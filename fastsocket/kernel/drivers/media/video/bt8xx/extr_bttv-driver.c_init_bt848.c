#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t type; } ;
struct bttv {int /*<<< orphan*/  saturation; int /*<<< orphan*/  contrast; int /*<<< orphan*/  hue; int /*<<< orphan*/  bright; scalar_t__ opt_lumafilter; scalar_t__ opt_adc_crush; scalar_t__ opt_chroma_agc; TYPE_1__ c; } ;
struct TYPE_4__ {scalar_t__ no_video; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_ADC ; 
 int BT848_ADC_CRUSH ; 
 int BT848_ADC_RESERVED ; 
 int /*<<< orphan*/  BT848_CAP_CTL ; 
 int /*<<< orphan*/  BT848_COLOR_CTL ; 
 int BT848_COLOR_CTL_GAMMA ; 
 int BT848_CONTROL_LDEC ; 
 int /*<<< orphan*/  BT848_E_CONTROL ; 
 int /*<<< orphan*/  BT848_E_SCLOOP ; 
 int /*<<< orphan*/  BT848_E_VSCALE_HI ; 
 int /*<<< orphan*/  BT848_GPIO_DMA_CTL ; 
 int BT848_GPIO_DMA_CTL_GPINTC ; 
 int BT848_GPIO_DMA_CTL_GPINTI ; 
 int BT848_GPIO_DMA_CTL_PKTP_32 ; 
 int BT848_GPIO_DMA_CTL_PLTP1_16 ; 
 int BT848_GPIO_DMA_CTL_PLTP23_16 ; 
 int /*<<< orphan*/  BT848_IFORM ; 
 int BT848_IFORM_AUTO ; 
 int BT848_IFORM_XTAUTO ; 
 int /*<<< orphan*/  BT848_O_CONTROL ; 
 int /*<<< orphan*/  BT848_O_SCLOOP ; 
 int /*<<< orphan*/  BT848_O_VSCALE_HI ; 
 int BT848_SCLOOP_CAGC ; 
 int /*<<< orphan*/  BT848_WC_DOWN ; 
 int /*<<< orphan*/  BT848_WC_UP ; 
 int /*<<< orphan*/  bt848_bright (struct bttv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt848_contrast (struct bttv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt848_hue (struct bttv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt848_sat (struct bttv*,int /*<<< orphan*/ ) ; 
 TYPE_2__* bttv_tvcards ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_irqreg (struct bttv*) ; 
 int whitecrush_lower ; 
 int whitecrush_upper ; 

__attribute__((used)) static void init_bt848(struct bttv *btv)
{
	int val;

	if (bttv_tvcards[btv->c.type].no_video) {
		/* very basic init only */
		init_irqreg(btv);
		return;
	}

	btwrite(0x00, BT848_CAP_CTL);
	btwrite(BT848_COLOR_CTL_GAMMA, BT848_COLOR_CTL);
	btwrite(BT848_IFORM_XTAUTO | BT848_IFORM_AUTO, BT848_IFORM);

	/* set planar and packed mode trigger points and         */
	/* set rising edge of inverted GPINTR pin as irq trigger */
	btwrite(BT848_GPIO_DMA_CTL_PKTP_32|
		BT848_GPIO_DMA_CTL_PLTP1_16|
		BT848_GPIO_DMA_CTL_PLTP23_16|
		BT848_GPIO_DMA_CTL_GPINTC|
		BT848_GPIO_DMA_CTL_GPINTI,
		BT848_GPIO_DMA_CTL);

	val = btv->opt_chroma_agc ? BT848_SCLOOP_CAGC : 0;
	btwrite(val, BT848_E_SCLOOP);
	btwrite(val, BT848_O_SCLOOP);

	btwrite(0x20, BT848_E_VSCALE_HI);
	btwrite(0x20, BT848_O_VSCALE_HI);
	btwrite(BT848_ADC_RESERVED | (btv->opt_adc_crush ? BT848_ADC_CRUSH : 0),
		BT848_ADC);

	btwrite(whitecrush_upper, BT848_WC_UP);
	btwrite(whitecrush_lower, BT848_WC_DOWN);

	if (btv->opt_lumafilter) {
		btwrite(0, BT848_E_CONTROL);
		btwrite(0, BT848_O_CONTROL);
	} else {
		btwrite(BT848_CONTROL_LDEC, BT848_E_CONTROL);
		btwrite(BT848_CONTROL_LDEC, BT848_O_CONTROL);
	}

	bt848_bright(btv,   btv->bright);
	bt848_hue(btv,      btv->hue);
	bt848_contrast(btv, btv->contrast);
	bt848_sat(btv,      btv->saturation);

	/* interrupt */
	init_irqreg(btv);
}