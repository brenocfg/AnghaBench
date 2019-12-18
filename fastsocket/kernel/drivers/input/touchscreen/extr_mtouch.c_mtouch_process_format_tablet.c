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
struct mtouch {scalar_t__ idx; int /*<<< orphan*/  data; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 scalar_t__ MTOUCH_FORMAT_TABLET_LENGTH ; 
 int /*<<< orphan*/  MTOUCH_GET_TOUCHED (int /*<<< orphan*/ ) ; 
 scalar_t__ MTOUCH_GET_XC (int /*<<< orphan*/ ) ; 
 scalar_t__ MTOUCH_GET_YC (int /*<<< orphan*/ ) ; 
 scalar_t__ MTOUCH_MAX_YC ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void mtouch_process_format_tablet(struct mtouch *mtouch)
{
	struct input_dev *dev = mtouch->dev;

	if (MTOUCH_FORMAT_TABLET_LENGTH == ++mtouch->idx) {
		input_report_abs(dev, ABS_X, MTOUCH_GET_XC(mtouch->data));
		input_report_abs(dev, ABS_Y, MTOUCH_MAX_YC - MTOUCH_GET_YC(mtouch->data));
		input_report_key(dev, BTN_TOUCH, MTOUCH_GET_TOUCHED(mtouch->data));
		input_sync(dev);

		mtouch->idx = 0;
	}
}