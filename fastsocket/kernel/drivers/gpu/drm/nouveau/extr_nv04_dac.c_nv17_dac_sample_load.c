#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct nouveau_gpio {int (* get ) (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* set ) (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_4__ {int tvdactestval; int dactestval; } ;
struct nouveau_drm {int /*<<< orphan*/  device; TYPE_1__ vbios; } ;
struct nouveau_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct dcb_output {scalar_t__ type; } ;
struct TYPE_6__ {struct dcb_output* dcb; } ;
struct TYPE_5__ {scalar_t__ card_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_GPIO_TVDAC0 ; 
 int /*<<< orphan*/  DCB_GPIO_TVDAC1 ; 
 scalar_t__ DCB_OUTPUT_TV ; 
 int NVReadRAMDAC (struct drm_device*,int,scalar_t__) ; 
 int NVReadVgaCrtc (struct drm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,int,scalar_t__,int) ; 
 scalar_t__ NV_40 ; 
 int /*<<< orphan*/  NV_CIO_CRE_RPC1_INDEX ; 
 int /*<<< orphan*/  NV_PBUS_POWERCTRL_2 ; 
 int /*<<< orphan*/  NV_PBUS_POWERCTRL_4 ; 
 scalar_t__ NV_PRAMDAC_DACCLK ; 
 scalar_t__ NV_PRAMDAC_TESTPOINT_DATA ; 
 int NV_PRAMDAC_TESTPOINT_DATA_NOTBLANK ; 
 scalar_t__ NV_PRAMDAC_TEST_CONTROL ; 
 int NV_PRAMDAC_TEST_CONTROL_PWRDWN_DAC_OFF ; 
 int NV_PRAMDAC_TEST_CONTROL_TP_INS_EN_ASSERTED ; 
 int RGB_TEST_DATA (int,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_3__* nouveau_encoder (struct drm_encoder*) ; 
 struct nouveau_gpio* nouveau_gpio (struct nouveau_device*) ; 
 int nv04_dac_output_offset (struct drm_encoder*) ; 
 TYPE_2__* nv_device (int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nouveau_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub4 (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub5 (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub6 (struct nouveau_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

uint32_t nv17_dac_sample_load(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_gpio *gpio = nouveau_gpio(device);
	struct dcb_output *dcb = nouveau_encoder(encoder)->dcb;
	uint32_t sample, testval, regoffset = nv04_dac_output_offset(encoder);
	uint32_t saved_powerctrl_2 = 0, saved_powerctrl_4 = 0, saved_routput,
		saved_rtest_ctrl, saved_gpio0 = 0, saved_gpio1 = 0, temp, routput;
	int head;

#define RGB_TEST_DATA(r, g, b) (r << 0 | g << 10 | b << 20)
	if (dcb->type == DCB_OUTPUT_TV) {
		testval = RGB_TEST_DATA(0xa0, 0xa0, 0xa0);

		if (drm->vbios.tvdactestval)
			testval = drm->vbios.tvdactestval;
	} else {
		testval = RGB_TEST_DATA(0x140, 0x140, 0x140); /* 0x94050140 */

		if (drm->vbios.dactestval)
			testval = drm->vbios.dactestval;
	}

	saved_rtest_ctrl = NVReadRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset,
		      saved_rtest_ctrl & ~NV_PRAMDAC_TEST_CONTROL_PWRDWN_DAC_OFF);

	saved_powerctrl_2 = nv_rd32(device, NV_PBUS_POWERCTRL_2);

	nv_wr32(device, NV_PBUS_POWERCTRL_2, saved_powerctrl_2 & 0xd7ffffff);
	if (regoffset == 0x68) {
		saved_powerctrl_4 = nv_rd32(device, NV_PBUS_POWERCTRL_4);
		nv_wr32(device, NV_PBUS_POWERCTRL_4, saved_powerctrl_4 & 0xffffffcf);
	}

	if (gpio) {
		saved_gpio1 = gpio->get(gpio, 0, DCB_GPIO_TVDAC1, 0xff);
		saved_gpio0 = gpio->get(gpio, 0, DCB_GPIO_TVDAC0, 0xff);
		gpio->set(gpio, 0, DCB_GPIO_TVDAC1, 0xff, dcb->type == DCB_OUTPUT_TV);
		gpio->set(gpio, 0, DCB_GPIO_TVDAC0, 0xff, dcb->type == DCB_OUTPUT_TV);
	}

	msleep(4);

	saved_routput = NVReadRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset);
	head = (saved_routput & 0x100) >> 8;

	/* if there's a spare crtc, using it will minimise flicker */
	if (!(NVReadVgaCrtc(dev, head, NV_CIO_CRE_RPC1_INDEX) & 0xC0))
		head ^= 1;

	/* nv driver and nv31 use 0xfffffeee, nv34 and 6600 use 0xfffffece */
	routput = (saved_routput & 0xfffffece) | head << 8;

	if (nv_device(drm->device)->card_type >= NV_40) {
		if (dcb->type == DCB_OUTPUT_TV)
			routput |= 0x1a << 16;
		else
			routput &= ~(0x1a << 16);
	}

	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset, routput);
	msleep(1);

	temp = NVReadRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset, temp | 1);

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TESTPOINT_DATA,
		      NV_PRAMDAC_TESTPOINT_DATA_NOTBLANK | testval);
	temp = NVReadRAMDAC(dev, head, NV_PRAMDAC_TEST_CONTROL);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TEST_CONTROL,
		      temp | NV_PRAMDAC_TEST_CONTROL_TP_INS_EN_ASSERTED);
	msleep(5);

	sample = NVReadRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset);
	/* do it again just in case it's a residual current */
	sample &= NVReadRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset);

	temp = NVReadRAMDAC(dev, head, NV_PRAMDAC_TEST_CONTROL);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TEST_CONTROL,
		      temp & ~NV_PRAMDAC_TEST_CONTROL_TP_INS_EN_ASSERTED);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_TESTPOINT_DATA, 0);

	/* bios does something more complex for restoring, but I think this is good enough */
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_DACCLK + regoffset, saved_routput);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL + regoffset, saved_rtest_ctrl);
	if (regoffset == 0x68)
		nv_wr32(device, NV_PBUS_POWERCTRL_4, saved_powerctrl_4);
	nv_wr32(device, NV_PBUS_POWERCTRL_2, saved_powerctrl_2);

	if (gpio) {
		gpio->set(gpio, 0, DCB_GPIO_TVDAC1, 0xff, saved_gpio1);
		gpio->set(gpio, 0, DCB_GPIO_TVDAC0, 0xff, saved_gpio0);
	}

	return sample;
}