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
typedef  int u8 ;
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ADC_CHANNEL_TS_X ; 
 int /*<<< orphan*/  ADC_CHANNEL_TS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  HP680_TS_IRQ ; 
 int /*<<< orphan*/  PHDR ; 
 int PHDR_TS_PEN_DOWN ; 
 int /*<<< orphan*/  SCPDR ; 
 int SCPDR_TS_SCAN_ENABLE ; 
 int SCPDR_TS_SCAN_X ; 
 int SCPDR_TS_SCAN_Y ; 
 int adc_single (int /*<<< orphan*/ ) ; 
 int ctrl_inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp680_ts_dev ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void do_softint(struct work_struct *work)
{
	int absx = 0, absy = 0;
	u8 scpdr;
	int touched = 0;

	if (ctrl_inb(PHDR) & PHDR_TS_PEN_DOWN) {
		scpdr = ctrl_inb(SCPDR);
		scpdr |= SCPDR_TS_SCAN_ENABLE;
		scpdr &= ~SCPDR_TS_SCAN_Y;
		ctrl_outb(scpdr, SCPDR);
		udelay(30);

		absy = adc_single(ADC_CHANNEL_TS_Y);

		scpdr = ctrl_inb(SCPDR);
		scpdr |= SCPDR_TS_SCAN_Y;
		scpdr &= ~SCPDR_TS_SCAN_X;
		ctrl_outb(scpdr, SCPDR);
		udelay(30);

		absx = adc_single(ADC_CHANNEL_TS_X);

		scpdr = ctrl_inb(SCPDR);
		scpdr |= SCPDR_TS_SCAN_X;
		scpdr &= ~SCPDR_TS_SCAN_ENABLE;
		ctrl_outb(scpdr, SCPDR);
		udelay(100);
		touched = ctrl_inb(PHDR) & PHDR_TS_PEN_DOWN;
	}

	if (touched) {
		input_report_key(hp680_ts_dev, BTN_TOUCH, 1);
		input_report_abs(hp680_ts_dev, ABS_X, absx);
		input_report_abs(hp680_ts_dev, ABS_Y, absy);
	} else {
		input_report_key(hp680_ts_dev, BTN_TOUCH, 0);
	}

	input_sync(hp680_ts_dev);
	enable_irq(HP680_TS_IRQ);
}