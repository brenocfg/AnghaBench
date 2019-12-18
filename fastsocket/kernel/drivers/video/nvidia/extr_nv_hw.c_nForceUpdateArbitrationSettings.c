#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct nvidia_par {int Chipset; unsigned int CrystalFreqKHz; int /*<<< orphan*/  PRAMDAC0; } ;
struct TYPE_5__ {char pix_bpp; int memory_type; int memory_width; int mem_latency; int mem_aligned; int mem_page_miss; unsigned int pclk_khz; unsigned int mclk_khz; unsigned int nvclk_khz; scalar_t__ gr_during_vid; scalar_t__ enable_mp; scalar_t__ enable_video; } ;
typedef  TYPE_1__ nv10_sim_state ;
struct TYPE_6__ {int graphics_burst_size; int graphics_lwm; scalar_t__ valid; } ;
typedef  TYPE_2__ nv10_fifo_info ;

/* Variables and functions */
 unsigned int NV_RD32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv10CalcArbitration (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_bus_and_slot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,...) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void nForceUpdateArbitrationSettings(unsigned VClk,
					    unsigned pixelDepth,
					    unsigned *burst,
					    unsigned *lwm,
					    struct nvidia_par *par)
{
	nv10_fifo_info fifo_data;
	nv10_sim_state sim_data;
	unsigned int M, N, P, pll, MClk, NVClk, memctrl;
	struct pci_dev *dev;

	if ((par->Chipset & 0x0FF0) == 0x01A0) {
		unsigned int uMClkPostDiv;
		dev = pci_get_bus_and_slot(0, 3);
		pci_read_config_dword(dev, 0x6C, &uMClkPostDiv);
		uMClkPostDiv = (uMClkPostDiv >> 8) & 0xf;

		if (!uMClkPostDiv)
			uMClkPostDiv = 4;
		MClk = 400000 / uMClkPostDiv;
	} else {
		dev = pci_get_bus_and_slot(0, 5);
		pci_read_config_dword(dev, 0x4c, &MClk);
		MClk /= 1000;
	}
	pci_dev_put(dev);
	pll = NV_RD32(par->PRAMDAC0, 0x0500);
	M = (pll >> 0) & 0xFF;
	N = (pll >> 8) & 0xFF;
	P = (pll >> 16) & 0x0F;
	NVClk = (N * par->CrystalFreqKHz / M) >> P;
	sim_data.pix_bpp = (char)pixelDepth;
	sim_data.enable_video = 0;
	sim_data.enable_mp = 0;
	dev = pci_get_bus_and_slot(0, 1);
	pci_read_config_dword(dev, 0x7C, &sim_data.memory_type);
	pci_dev_put(dev);
	sim_data.memory_type = (sim_data.memory_type >> 12) & 1;
	sim_data.memory_width = 64;

	dev = pci_get_bus_and_slot(0, 3);
	pci_read_config_dword(dev, 0, &memctrl);
	pci_dev_put(dev);
	memctrl >>= 16;

	if ((memctrl == 0x1A9) || (memctrl == 0x1AB) || (memctrl == 0x1ED)) {
		u32 dimm[3];

		dev = pci_get_bus_and_slot(0, 2);
		pci_read_config_dword(dev, 0x40, &dimm[0]);
		dimm[0] = (dimm[0] >> 8) & 0x4f;
		pci_read_config_dword(dev, 0x44, &dimm[1]);
		dimm[1] = (dimm[1] >> 8) & 0x4f;
		pci_read_config_dword(dev, 0x48, &dimm[2]);
		dimm[2] = (dimm[2] >> 8) & 0x4f;

		if ((dimm[0] + dimm[1]) != dimm[2]) {
			printk("nvidiafb: your nForce DIMMs are not arranged "
			       "in optimal banks!\n");
		}
		pci_dev_put(dev);
	}

	sim_data.mem_latency = 3;
	sim_data.mem_aligned = 1;
	sim_data.mem_page_miss = 10;
	sim_data.gr_during_vid = 0;
	sim_data.pclk_khz = VClk;
	sim_data.mclk_khz = MClk;
	sim_data.nvclk_khz = NVClk;
	nv10CalcArbitration(&fifo_data, &sim_data);
	if (fifo_data.valid) {
		int b = fifo_data.graphics_burst_size >> 4;
		*burst = 0;
		while (b >>= 1)
			(*burst)++;
		*lwm = fifo_data.graphics_lwm >> 3;
	}
}