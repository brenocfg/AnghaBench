#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int RamAmountKBytes; int RamBandwidthKBytesPerSec; int CrystalFreqKHz; int CursorStart; int VBlankBit; int MaxVClockFreqKHz; int /*<<< orphan*/  twoHeads; int /*<<< orphan*/  LockUnlock; int /*<<< orphan*/  SetSurfaces3D; int /*<<< orphan*/  SetSurfaces2D; int /*<<< orphan*/  SetStartAddress; int /*<<< orphan*/  UnloadStateExt; int /*<<< orphan*/  LoadStateExt; int /*<<< orphan*/  ShowHideCursor; int /*<<< orphan*/  Busy; int /*<<< orphan*/ * CURSOR; int /*<<< orphan*/  PEXTDEV; int /*<<< orphan*/  PFB; int /*<<< orphan*/  PMC; } ;
typedef  TYPE_1__ RIVA_HW_INST ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LoadStateExt ; 
 unsigned int NV_CHIP_0x01F0 ; 
 unsigned int NV_CHIP_IGEFORCE2 ; 
 int NV_RD32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NV_WR32 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SetStartAddress ; 
 int /*<<< orphan*/  ShowHideCursor ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnloadStateExt ; 
 int /*<<< orphan*/  nv10Busy ; 
 int /*<<< orphan*/  nv10SetSurfaces2D ; 
 int /*<<< orphan*/  nv10SetSurfaces3D ; 
 int /*<<< orphan*/  nv4LockUnlock ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_bus_and_slot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 

__attribute__((used)) static void nv10GetConfig
(
    RIVA_HW_INST *chip,
    unsigned int chipset
)
{
    struct pci_dev* dev;
    u32 amt;

#ifdef __BIG_ENDIAN
    /* turn on big endian register access */
    if(!(NV_RD32(chip->PMC, 0x00000004) & 0x01000001))
    	NV_WR32(chip->PMC, 0x00000004, 0x01000001);
#endif

    /*
     * Fill in chip configuration.
     */
    if(chipset == NV_CHIP_IGEFORCE2) {
        dev = pci_get_bus_and_slot(0, 1);
        pci_read_config_dword(dev, 0x7C, &amt);
        pci_dev_put(dev);
        chip->RamAmountKBytes = (((amt >> 6) & 31) + 1) * 1024;
    } else if(chipset == NV_CHIP_0x01F0) {
        dev = pci_get_bus_and_slot(0, 1);
        pci_read_config_dword(dev, 0x84, &amt);
        pci_dev_put(dev);
        chip->RamAmountKBytes = (((amt >> 4) & 127) + 1) * 1024;
    } else {
        switch ((NV_RD32(chip->PFB, 0x0000020C) >> 20) & 0x000000FF)
        {
            case 0x02:
                chip->RamAmountKBytes = 1024 * 2;
                break;
            case 0x04:
                chip->RamAmountKBytes = 1024 * 4;
                break;
            case 0x08:
                chip->RamAmountKBytes = 1024 * 8;
                break;
            case 0x10:
                chip->RamAmountKBytes = 1024 * 16;
                break;
            case 0x20:
                chip->RamAmountKBytes = 1024 * 32;
                break;
            case 0x40:
                chip->RamAmountKBytes = 1024 * 64;
                break;
            case 0x80:
                chip->RamAmountKBytes = 1024 * 128;
                break;
            default:
                chip->RamAmountKBytes = 1024 * 16;
                break;
        }
    }
    switch ((NV_RD32(chip->PFB, 0x00000000) >> 3) & 0x00000003)
    {
        case 3:
            chip->RamBandwidthKBytesPerSec = 800000;
            break;
        default:
            chip->RamBandwidthKBytesPerSec = 1000000;
            break;
    }
    chip->CrystalFreqKHz = (NV_RD32(chip->PEXTDEV, 0x0000) & (1 << 6)) ?
	14318 : 13500;

    switch (chipset & 0x0ff0) {
    case 0x0170:
    case 0x0180:
    case 0x01F0:
    case 0x0250:
    case 0x0280:
    case 0x0300:
    case 0x0310:
    case 0x0320:
    case 0x0330:
    case 0x0340:
       if(NV_RD32(chip->PEXTDEV, 0x0000) & (1 << 22))
           chip->CrystalFreqKHz = 27000;
       break;
    default:
       break;
    }

    chip->CursorStart      = (chip->RamAmountKBytes - 128) * 1024;
    chip->CURSOR           = NULL;  /* can't set this here */
    chip->VBlankBit        = 0x00000001;
    chip->MaxVClockFreqKHz = 350000;
    /*
     * Set chip functions.
     */
    chip->Busy            = nv10Busy;
    chip->ShowHideCursor  = ShowHideCursor;
    chip->LoadStateExt    = LoadStateExt;
    chip->UnloadStateExt  = UnloadStateExt;
    chip->SetStartAddress = SetStartAddress;
    chip->SetSurfaces2D   = nv10SetSurfaces2D;
    chip->SetSurfaces3D   = nv10SetSurfaces3D;
    chip->LockUnlock      = nv4LockUnlock;

    switch(chipset & 0x0ff0) {
    case 0x0110:
    case 0x0170:
    case 0x0180:
    case 0x01F0:
    case 0x0250:
    case 0x0280:
    case 0x0300:
    case 0x0310:
    case 0x0320:
    case 0x0330:
    case 0x0340:
        chip->twoHeads = TRUE;
        break;
    default:
        chip->twoHeads = FALSE;
        break;
    }
}