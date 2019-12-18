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
struct tgfx {int sticks; int /*<<< orphan*/  timer; TYPE_1__* pd; struct input_dev** dev; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_THUMB ; 
 int /*<<< orphan*/  BTN_THUMB2 ; 
 int /*<<< orphan*/  BTN_TOP ; 
 int /*<<< orphan*/  BTN_TOP2 ; 
 int /*<<< orphan*/  BTN_TRIGGER ; 
 int TGFX_DOWN ; 
 int TGFX_LEFT ; 
 scalar_t__ TGFX_REFRESH_TIME ; 
 int TGFX_RIGHT ; 
 int TGFX_THUMB ; 
 int TGFX_THUMB2 ; 
 int TGFX_TOP ; 
 int TGFX_TOP2 ; 
 int TGFX_TRIGGER ; 
 int TGFX_UP ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int parport_read_control (int /*<<< orphan*/ ) ; 
 int parport_read_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_write_data (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tgfx_timer(unsigned long private)
{
	struct tgfx *tgfx = (void *) private;
	struct input_dev *dev;
	int data1, data2, i;

	for (i = 0; i < 7; i++)
		if (tgfx->sticks & (1 << i)) {

			dev = tgfx->dev[i];

			parport_write_data(tgfx->pd->port, ~(1 << i));
			data1 = parport_read_status(tgfx->pd->port) ^ 0x7f;
			data2 = parport_read_control(tgfx->pd->port) ^ 0x04;	/* CAVEAT parport */

			input_report_abs(dev, ABS_X, !!(data1 & TGFX_RIGHT) - !!(data1 & TGFX_LEFT));
			input_report_abs(dev, ABS_Y, !!(data1 & TGFX_DOWN ) - !!(data1 & TGFX_UP  ));

			input_report_key(dev, BTN_TRIGGER, (data1 & TGFX_TRIGGER));
			input_report_key(dev, BTN_THUMB,   (data2 & TGFX_THUMB  ));
			input_report_key(dev, BTN_THUMB2,  (data2 & TGFX_THUMB2 ));
			input_report_key(dev, BTN_TOP,     (data2 & TGFX_TOP    ));
			input_report_key(dev, BTN_TOP2,    (data2 & TGFX_TOP2   ));

			input_sync(dev);
		}

	mod_timer(&tgfx->timer, jiffies + TGFX_REFRESH_TIME);
}