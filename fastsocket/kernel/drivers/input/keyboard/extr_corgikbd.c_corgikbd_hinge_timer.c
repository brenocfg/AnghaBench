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
struct corgikbd {int /*<<< orphan*/  htimer; int /*<<< orphan*/  lock; int /*<<< orphan*/  input; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORGI_GPIO_AK_INT ; 
 unsigned long CORGI_SCP_SWA ; 
 unsigned long CORGI_SCP_SWB ; 
 int /*<<< orphan*/  HINGE_SCAN_INTERVAL ; 
 scalar_t__ HINGE_STABLE_COUNT ; 
 scalar_t__ READ_GPIO_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCOOP_GPRR ; 
 int /*<<< orphan*/  SW_HEADPHONE_INSERT ; 
 int /*<<< orphan*/  SW_LID ; 
 int /*<<< orphan*/  SW_TABLET_MODE ; 
 TYPE_1__ corgiscoop_device ; 
 scalar_t__ hinge_count ; 
 int /*<<< orphan*/  input_report_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned long read_scoop_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long sharpsl_hinge_state ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void corgikbd_hinge_timer(unsigned long data)
{
	struct corgikbd *corgikbd_data = (struct corgikbd *) data;
	unsigned long gprr;
	unsigned long flags;

	gprr = read_scoop_reg(&corgiscoop_device.dev, SCOOP_GPRR) & (CORGI_SCP_SWA | CORGI_SCP_SWB);
	gprr |= (READ_GPIO_BIT(CORGI_GPIO_AK_INT) != 0);
	if (gprr != sharpsl_hinge_state) {
		hinge_count = 0;
		sharpsl_hinge_state = gprr;
	} else if (hinge_count < HINGE_STABLE_COUNT) {
		hinge_count++;
		if (hinge_count >= HINGE_STABLE_COUNT) {
			spin_lock_irqsave(&corgikbd_data->lock, flags);

			input_report_switch(corgikbd_data->input, SW_LID, ((sharpsl_hinge_state & CORGI_SCP_SWA) != 0));
			input_report_switch(corgikbd_data->input, SW_TABLET_MODE, ((sharpsl_hinge_state & CORGI_SCP_SWB) != 0));
			input_report_switch(corgikbd_data->input, SW_HEADPHONE_INSERT, (READ_GPIO_BIT(CORGI_GPIO_AK_INT) != 0));
			input_sync(corgikbd_data->input);

			spin_unlock_irqrestore(&corgikbd_data->lock, flags);
		}
	}
	mod_timer(&corgikbd_data->htimer, jiffies + msecs_to_jiffies(HINGE_SCAN_INTERVAL));
}