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
 size_t NVDEV_ENGINE_BSP ; 
 size_t NVDEV_ENGINE_COPY0 ; 
 size_t NVDEV_ENGINE_COPY1 ; 
 size_t NVDEV_ENGINE_DISP ; 
 size_t NVDEV_ENGINE_DMAOBJ ; 
 size_t NVDEV_ENGINE_FIFO ; 
 size_t NVDEV_ENGINE_GR ; 
 size_t NVDEV_ENGINE_PPP ; 
 size_t NVDEV_ENGINE_SW ; 
 size_t NVDEV_ENGINE_VP ; 
 size_t NVDEV_SUBDEV_BAR ; 
 size_t NVDEV_SUBDEV_BUS ; 
 size_t NVDEV_SUBDEV_CLOCK ; 
 size_t NVDEV_SUBDEV_DEVINIT ; 
 size_t NVDEV_SUBDEV_FB ; 
 size_t NVDEV_SUBDEV_GPIO ; 
 size_t NVDEV_SUBDEV_I2C ; 
 size_t NVDEV_SUBDEV_IBUS ; 
 size_t NVDEV_SUBDEV_INSTMEM ; 
 size_t NVDEV_SUBDEV_LTCG ; 
 size_t NVDEV_SUBDEV_MC ; 
 size_t NVDEV_SUBDEV_MXM ; 
 size_t NVDEV_SUBDEV_THERM ; 
 size_t NVDEV_SUBDEV_TIMER ; 
 size_t NVDEV_SUBDEV_VBIOS ; 
 size_t NVDEV_SUBDEV_VM ; 
 int /*<<< orphan*/  nouveau_bios_oclass ; 
 int /*<<< orphan*/  nv04_timer_oclass ; 
 int /*<<< orphan*/  nv50_devinit_oclass ; 
 int /*<<< orphan*/  nv50_instmem_oclass ; 
 int /*<<< orphan*/  nv50_mxm_oclass ; 
 int /*<<< orphan*/  nv_fatal (struct nouveau_device*,char*) ; 
 int /*<<< orphan*/  nvc0_bar_oclass ; 
 int /*<<< orphan*/  nvc0_bus_oclass ; 
 int /*<<< orphan*/  nvc0_clock_oclass ; 
 int /*<<< orphan*/  nvc0_fb_oclass ; 
 int /*<<< orphan*/  nvc0_ltcg_oclass ; 
 int /*<<< orphan*/  nvc0_mc_oclass ; 
 int /*<<< orphan*/  nvc0_ppp_oclass ; 
 int /*<<< orphan*/  nvc0_software_oclass ; 
 int /*<<< orphan*/  nvc0_vmmgr_oclass ; 
 int /*<<< orphan*/  nvd0_dmaeng_oclass ; 
 int /*<<< orphan*/  nvd0_i2c_oclass ; 
 int /*<<< orphan*/  nvd0_therm_oclass ; 
 int /*<<< orphan*/  nve0_bsp_oclass ; 
 int /*<<< orphan*/  nve0_copy0_oclass ; 
 int /*<<< orphan*/  nve0_copy1_oclass ; 
 int /*<<< orphan*/  nve0_disp_oclass ; 
 int /*<<< orphan*/  nve0_fifo_oclass ; 
 int /*<<< orphan*/  nve0_gpio_oclass ; 
 int /*<<< orphan*/  nve0_graph_oclass ; 
 int /*<<< orphan*/  nve0_ibus_oclass ; 
 int /*<<< orphan*/  nve0_vp_oclass ; 

int
nve0_identify(struct nouveau_device *device)
{
	switch (device->chipset) {
	case 0xe4:
		device->cname = "GK104";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nve0_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nvd0_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nvc0_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nvd0_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nvc0_mc_oclass;
		device->oclass[NVDEV_SUBDEV_BUS    ] = &nvc0_bus_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nvc0_fb_oclass;
		device->oclass[NVDEV_SUBDEV_LTCG   ] = &nvc0_ltcg_oclass;
		device->oclass[NVDEV_SUBDEV_IBUS   ] = &nve0_ibus_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nvc0_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nvc0_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nvd0_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nve0_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nvc0_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nve0_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nve0_disp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nve0_copy0_oclass;
		device->oclass[NVDEV_ENGINE_COPY1  ] = &nve0_copy1_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nve0_bsp_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nve0_vp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nvc0_ppp_oclass;
		break;
	case 0xe7:
		device->cname = "GK107";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nve0_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nvd0_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nvc0_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nvd0_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nvc0_mc_oclass;
		device->oclass[NVDEV_SUBDEV_BUS    ] = &nvc0_bus_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nvc0_fb_oclass;
		device->oclass[NVDEV_SUBDEV_LTCG   ] = &nvc0_ltcg_oclass;
		device->oclass[NVDEV_SUBDEV_IBUS   ] = &nve0_ibus_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nvc0_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nvc0_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nvd0_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nve0_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nvc0_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nve0_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nve0_disp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nve0_copy0_oclass;
		device->oclass[NVDEV_ENGINE_COPY1  ] = &nve0_copy1_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nve0_bsp_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nve0_vp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nvc0_ppp_oclass;
		break;
	case 0xe6:
		device->cname = "GK106";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nve0_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nvd0_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nvc0_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nvd0_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nvc0_mc_oclass;
		device->oclass[NVDEV_SUBDEV_BUS    ] = &nvc0_bus_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nvc0_fb_oclass;
		device->oclass[NVDEV_SUBDEV_LTCG   ] = &nvc0_ltcg_oclass;
		device->oclass[NVDEV_SUBDEV_IBUS   ] = &nve0_ibus_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nvc0_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nvc0_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nvd0_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nve0_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nvc0_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nve0_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nve0_disp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nve0_copy0_oclass;
		device->oclass[NVDEV_ENGINE_COPY1  ] = &nve0_copy1_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nve0_bsp_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nve0_vp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nvc0_ppp_oclass;
		break;
	default:
		nv_fatal(device, "unknown Kepler chipset\n");
		return -EINVAL;
	}

	return 0;
}