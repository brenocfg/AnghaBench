#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_7__ {char pix_bpp; unsigned int memory_type; int memory_width; int mem_latency; int mem_aligned; int mem_page_miss; unsigned int pclk_khz; unsigned int mclk_khz; unsigned int nvclk_khz; scalar_t__ gr_during_vid; scalar_t__ enable_mp; scalar_t__ enable_video; } ;
typedef  TYPE_1__ nv10_sim_state ;
struct TYPE_8__ {int graphics_burst_size; int graphics_lwm; scalar_t__ valid; } ;
typedef  TYPE_2__ nv10_fifo_info ;
struct TYPE_9__ {unsigned int CrystalFreqKHz; int /*<<< orphan*/ * PRAMDAC0; } ;
typedef  TYPE_3__ RIVA_HW_INST ;

/* Variables and functions */
 unsigned int NV_RD32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv10CalcArbitration (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_bus_and_slot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,unsigned int*) ; 

__attribute__((used)) static void nForceUpdateArbitrationSettings
(
    unsigned      VClk,
    unsigned      pixelDepth,
    unsigned     *burst,
    unsigned     *lwm,
    RIVA_HW_INST *chip
)
{
    nv10_fifo_info fifo_data;
    nv10_sim_state sim_data;
    unsigned int M, N, P, pll, MClk, NVClk;
    unsigned int uMClkPostDiv;
    struct pci_dev *dev;

    dev = pci_get_bus_and_slot(0, 3);
    pci_read_config_dword(dev, 0x6C, &uMClkPostDiv);
    pci_dev_put(dev);
    uMClkPostDiv = (uMClkPostDiv >> 8) & 0xf;

    if(!uMClkPostDiv) uMClkPostDiv = 4;
    MClk = 400000 / uMClkPostDiv;

    pll = NV_RD32(&chip->PRAMDAC0[0x00000500/4], 0);
    M = (pll >> 0)  & 0xFF; N = (pll >> 8)  & 0xFF; P = (pll >> 16) & 0x0F;
    NVClk  = (N * chip->CrystalFreqKHz / M) >> P;
    sim_data.pix_bpp        = (char)pixelDepth;
    sim_data.enable_video   = 0;
    sim_data.enable_mp      = 0;

    dev = pci_get_bus_and_slot(0, 1);
    pci_read_config_dword(dev, 0x7C, &sim_data.memory_type);
    pci_dev_put(dev);
    sim_data.memory_type    = (sim_data.memory_type >> 12) & 1;

    sim_data.memory_width   = 64;
    sim_data.mem_latency    = 3;
    sim_data.mem_aligned    = 1;
    sim_data.mem_page_miss  = 10;
    sim_data.gr_during_vid  = 0;
    sim_data.pclk_khz       = VClk;
    sim_data.mclk_khz       = MClk;
    sim_data.nvclk_khz      = NVClk;
    nv10CalcArbitration(&fifo_data, &sim_data);
    if (fifo_data.valid)
    {
        int  b = fifo_data.graphics_burst_size >> 4;
        *burst = 0;
        while (b >>= 1)
	    (*burst)++;
        *lwm   = fifo_data.graphics_lwm >> 3;
    }
}