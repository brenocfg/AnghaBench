#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct wm97xx {int /*<<< orphan*/  input_dev; TYPE_1__* touch_dev; } ;
struct atmel_wm97xx {int x; int y; struct wm97xx* wm; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int AC97C_OVRUN ; 
 int AC97C_RXRDY ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  CBRHR ; 
 int /*<<< orphan*/  CBSR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int WM97XX_ADCSEL_PRES ; 
 int WM97XX_ADCSEL_X ; 
 int WM97XX_ADCSEL_Y ; 
 int WM97XX_ADCSRC_MASK ; 
 int WM97XX_PEN_DOWN ; 
 int ac97c_readl (struct atmel_wm97xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ pressure ; 

__attribute__((used)) static irqreturn_t atmel_wm97xx_channel_b_interrupt(int irq, void *dev_id)
{
	struct atmel_wm97xx *atmel_wm97xx = dev_id;
	struct wm97xx *wm = atmel_wm97xx->wm;
	int status = ac97c_readl(atmel_wm97xx, CBSR);
	irqreturn_t retval = IRQ_NONE;

	if (status & AC97C_OVRUN) {
		dev_dbg(&wm->touch_dev->dev, "AC97C overrun\n");
		ac97c_readl(atmel_wm97xx, CBRHR);
		retval = IRQ_HANDLED;
	} else if (status & AC97C_RXRDY) {
		u16 data;
		u16 value;
		u16 source;
		u16 pen_down;

		data = ac97c_readl(atmel_wm97xx, CBRHR);
		value = data & 0x0fff;
		source = data & WM97XX_ADCSRC_MASK;
		pen_down = (data & WM97XX_PEN_DOWN) >> 8;

		if (source == WM97XX_ADCSEL_X)
			atmel_wm97xx->x = value;
		if (source == WM97XX_ADCSEL_Y)
			atmel_wm97xx->y = value;

		if (!pressure && source == WM97XX_ADCSEL_Y) {
			input_report_abs(wm->input_dev, ABS_X, atmel_wm97xx->x);
			input_report_abs(wm->input_dev, ABS_Y, atmel_wm97xx->y);
			input_report_key(wm->input_dev, BTN_TOUCH, pen_down);
			input_sync(wm->input_dev);
		} else if (pressure && source == WM97XX_ADCSEL_PRES) {
			input_report_abs(wm->input_dev, ABS_X, atmel_wm97xx->x);
			input_report_abs(wm->input_dev, ABS_Y, atmel_wm97xx->y);
			input_report_abs(wm->input_dev, ABS_PRESSURE, value);
			input_report_key(wm->input_dev, BTN_TOUCH, value);
			input_sync(wm->input_dev);
		}

		retval = IRQ_HANDLED;
	}

	return retval;
}