#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nouveau_device {int chipset; char* cname; int /*<<< orphan*/ ** oclass; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NVDEV_ENGINE_DISP ; 
 size_t NVDEV_ENGINE_DMAOBJ ; 
 size_t NVDEV_ENGINE_FIFO ; 
 size_t NVDEV_ENGINE_GR ; 
 size_t NVDEV_ENGINE_SW ; 
 size_t NVDEV_SUBDEV_BUS ; 
 size_t NVDEV_SUBDEV_CLOCK ; 
 size_t NVDEV_SUBDEV_DEVINIT ; 
 size_t NVDEV_SUBDEV_FB ; 
 size_t NVDEV_SUBDEV_I2C ; 
 size_t NVDEV_SUBDEV_INSTMEM ; 
 size_t NVDEV_SUBDEV_MC ; 
 size_t NVDEV_SUBDEV_TIMER ; 
 size_t NVDEV_SUBDEV_VBIOS ; 
 size_t NVDEV_SUBDEV_VM ; 
 int /*<<< orphan*/  nouveau_bios_oclass ; 
 int /*<<< orphan*/  nv04_bus_oclass ; 
 int /*<<< orphan*/  nv04_clock_oclass ; 
 int /*<<< orphan*/  nv04_devinit_oclass ; 
 int /*<<< orphan*/  nv04_disp_oclass ; 
 int /*<<< orphan*/  nv04_dmaeng_oclass ; 
 int /*<<< orphan*/  nv04_fb_oclass ; 
 int /*<<< orphan*/  nv04_fifo_oclass ; 
 int /*<<< orphan*/  nv04_graph_oclass ; 
 int /*<<< orphan*/  nv04_i2c_oclass ; 
 int /*<<< orphan*/  nv04_instmem_oclass ; 
 int /*<<< orphan*/  nv04_mc_oclass ; 
 int /*<<< orphan*/  nv04_software_oclass ; 
 int /*<<< orphan*/  nv04_timer_oclass ; 
 int /*<<< orphan*/  nv04_vmmgr_oclass ; 
 int /*<<< orphan*/  nv05_devinit_oclass ; 
 int /*<<< orphan*/  nv_fatal (struct nouveau_device*,char*) ; 

int
nv04_identify(struct nouveau_device *device)
{
	switch (device->chipset) {
	case 0x04:
		device->cname = "NV04";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nv04_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv04_clock_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv04_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_BUS    ] = &nv04_bus_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv04_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv04_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv04_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv04_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv04_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv04_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x05:
		device->cname = "NV05";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nv04_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv04_clock_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv05_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_BUS    ] = &nv04_bus_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv04_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv04_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv04_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv04_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv04_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv04_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	default:
		nv_fatal(device, "unknown RIVA chipset\n");
		return -EINVAL;
	}

	return 0;
}