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
struct TYPE_3__ {int RamAmountKBytes; int RamBandwidthKBytesPerSec; int CrystalFreqKHz; int VBlankBit; int MaxVClockFreqKHz; int /*<<< orphan*/  LockUnlock; int /*<<< orphan*/  SetSurfaces3D; int /*<<< orphan*/  SetSurfaces2D; int /*<<< orphan*/  SetStartAddress; int /*<<< orphan*/  UnloadStateExt; int /*<<< orphan*/  LoadStateExt; int /*<<< orphan*/  ShowHideCursor; int /*<<< orphan*/  Busy; int /*<<< orphan*/ * PRAMIN; int /*<<< orphan*/ * CURSOR; int /*<<< orphan*/  PEXTDEV; int /*<<< orphan*/  PFB; } ;
typedef  TYPE_1__ RIVA_HW_INST ;

/* Variables and functions */
 int /*<<< orphan*/  LoadStateExt ; 
 int NV_RD32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetStartAddress ; 
 int /*<<< orphan*/  ShowHideCursor ; 
 int /*<<< orphan*/  UnloadStateExt ; 
 int /*<<< orphan*/  nv4Busy ; 
 int /*<<< orphan*/  nv4LockUnlock ; 
 int /*<<< orphan*/  nv4SetSurfaces2D ; 
 int /*<<< orphan*/  nv4SetSurfaces3D ; 

__attribute__((used)) static void nv4GetConfig
(
    RIVA_HW_INST *chip
)
{
    /*
     * Fill in chip configuration.
     */
    if (NV_RD32(chip->PFB, 0x00000000) & 0x00000100)
    {
        chip->RamAmountKBytes = ((NV_RD32(chip->PFB, 0x00000000) >> 12) & 0x0F) * 1024 * 2
                              + 1024 * 2;
    }
    else
    {
        switch (NV_RD32(chip->PFB, 0x00000000) & 0x00000003)
        {
            case 0:
                chip->RamAmountKBytes = 1024 * 32;
                break;
            case 1:
                chip->RamAmountKBytes = 1024 * 4;
                break;
            case 2:
                chip->RamAmountKBytes = 1024 * 8;
                break;
            case 3:
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
    chip->CrystalFreqKHz   = (NV_RD32(chip->PEXTDEV, 0x00000000) & 0x00000040) ? 14318 : 13500;
    chip->CURSOR           = &(chip->PRAMIN[0x00010000/4 - 0x0800/4]);
    chip->VBlankBit        = 0x00000001;
    chip->MaxVClockFreqKHz = 350000;
    /*
     * Set chip functions.
     */
    chip->Busy            = nv4Busy;
    chip->ShowHideCursor  = ShowHideCursor;
    chip->LoadStateExt    = LoadStateExt;
    chip->UnloadStateExt  = UnloadStateExt;
    chip->SetStartAddress = SetStartAddress;
    chip->SetSurfaces2D   = nv4SetSurfaces2D;
    chip->SetSurfaces3D   = nv4SetSurfaces3D;
    chip->LockUnlock      = nv4LockUnlock;
}