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
struct sh_mobile_lcdc_priv {struct sh_mobile_lcdc_chan* ch; } ;
struct sh_mobile_lcdc_chan {int frame_end; scalar_t__ new_pan_offset; scalar_t__ pan_offset; struct sh_mobile_lcdc_priv* lcdc; scalar_t__ dma_handle; int /*<<< orphan*/  frame_end_wait; int /*<<< orphan*/  enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct sh_mobile_lcdc_chan*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long LDINTR_FS ; 
 int LDINTR_VEE ; 
 unsigned long LDINTR_VES ; 
 unsigned long LDRCNTR_MRS ; 
 unsigned long LDRCNTR_SRS ; 
 int /*<<< orphan*/  LDSA1R ; 
 int /*<<< orphan*/  _LDINTR ; 
 int /*<<< orphan*/  _LDRCNTR ; 
 int /*<<< orphan*/  _LDSR ; 
 int lcdc_chan_is_sublcd (struct sh_mobile_lcdc_chan*) ; 
 int lcdc_read (struct sh_mobile_lcdc_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (struct sh_mobile_lcdc_priv*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  lcdc_write_chan_mirror (struct sh_mobile_lcdc_chan*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_clk_off (struct sh_mobile_lcdc_priv*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sh_mobile_lcdc_irq(int irq, void *data)
{
	struct sh_mobile_lcdc_priv *priv = data;
	struct sh_mobile_lcdc_chan *ch;
	unsigned long tmp;
	unsigned long ldintr;
	int is_sub;
	int k;

	/* acknowledge interrupt */
	ldintr = tmp = lcdc_read(priv, _LDINTR);
	/*
	 * disable further VSYNC End IRQs, preserve all other enabled IRQs,
	 * write 0 to bits 0-6 to ack all triggered IRQs.
	 */
	tmp &= 0xffffff00 & ~LDINTR_VEE;
	lcdc_write(priv, _LDINTR, tmp);

	/* figure out if this interrupt is for main or sub lcd */
	is_sub = (lcdc_read(priv, _LDSR) & (1 << 10)) ? 1 : 0;

	/* wake up channel and disable clocks */
	for (k = 0; k < ARRAY_SIZE(priv->ch); k++) {
		ch = &priv->ch[k];

		if (!ch->enabled)
			continue;

		/* Frame Start */
		if (ldintr & LDINTR_FS) {
			if (is_sub == lcdc_chan_is_sublcd(ch)) {
				ch->frame_end = 1;
				wake_up(&ch->frame_end_wait);

				sh_mobile_lcdc_clk_off(priv);
			}
		}

		/* VSYNC End */
		if (ldintr & LDINTR_VES) {
			unsigned long ldrcntr = lcdc_read(priv, _LDRCNTR);
			/* Set the source address for the next refresh */
			lcdc_write_chan_mirror(ch, LDSA1R, ch->dma_handle +
					       ch->new_pan_offset);
			if (lcdc_chan_is_sublcd(ch))
				lcdc_write(ch->lcdc, _LDRCNTR,
					   ldrcntr ^ LDRCNTR_SRS);
			else
				lcdc_write(ch->lcdc, _LDRCNTR,
					   ldrcntr ^ LDRCNTR_MRS);
			ch->pan_offset = ch->new_pan_offset;
		}
	}

	return IRQ_HANDLED;
}