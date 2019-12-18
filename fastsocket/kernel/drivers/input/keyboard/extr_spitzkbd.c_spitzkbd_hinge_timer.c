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
struct spitzkbd {int /*<<< orphan*/  htimer; int /*<<< orphan*/  lock; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 unsigned long GPIO_bit (int /*<<< orphan*/ ) ; 
 unsigned long GPLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINGE_SCAN_INTERVAL ; 
 scalar_t__ HINGE_STABLE_COUNT ; 
 int /*<<< orphan*/  SPITZ_GPIO_AK_INT ; 
 int /*<<< orphan*/  SPITZ_GPIO_SWA ; 
 int /*<<< orphan*/  SPITZ_GPIO_SWB ; 
 int /*<<< orphan*/  SW_HEADPHONE_INSERT ; 
 int /*<<< orphan*/  SW_LID ; 
 int /*<<< orphan*/  SW_TABLET_MODE ; 
 scalar_t__ hinge_count ; 
 int /*<<< orphan*/  input_report_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned long sharpsl_hinge_state ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void spitzkbd_hinge_timer(unsigned long data)
{
	struct spitzkbd *spitzkbd_data = (struct spitzkbd *) data;
	unsigned long state;
	unsigned long flags;

	state = GPLR(SPITZ_GPIO_SWA) & (GPIO_bit(SPITZ_GPIO_SWA)|GPIO_bit(SPITZ_GPIO_SWB));
	state |= (GPLR(SPITZ_GPIO_AK_INT) & GPIO_bit(SPITZ_GPIO_AK_INT));
	if (state != sharpsl_hinge_state) {
		hinge_count = 0;
		sharpsl_hinge_state = state;
	} else if (hinge_count < HINGE_STABLE_COUNT) {
		hinge_count++;
	}

	if (hinge_count >= HINGE_STABLE_COUNT) {
		spin_lock_irqsave(&spitzkbd_data->lock, flags);

		input_report_switch(spitzkbd_data->input, SW_LID, ((GPLR(SPITZ_GPIO_SWA) & GPIO_bit(SPITZ_GPIO_SWA)) != 0));
		input_report_switch(spitzkbd_data->input, SW_TABLET_MODE, ((GPLR(SPITZ_GPIO_SWB) & GPIO_bit(SPITZ_GPIO_SWB)) != 0));
		input_report_switch(spitzkbd_data->input, SW_HEADPHONE_INSERT, ((GPLR(SPITZ_GPIO_AK_INT) & GPIO_bit(SPITZ_GPIO_AK_INT)) != 0));
		input_sync(spitzkbd_data->input);

		spin_unlock_irqrestore(&spitzkbd_data->lock, flags);
	} else {
		mod_timer(&spitzkbd_data->htimer, jiffies + msecs_to_jiffies(HINGE_SCAN_INTERVAL));
	}
}