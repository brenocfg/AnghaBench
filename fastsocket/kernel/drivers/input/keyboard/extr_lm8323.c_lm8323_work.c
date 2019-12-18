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
typedef  int u8 ;
struct work_struct {int dummy; } ;
struct lm8323_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/ * pwm; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int INT_ERROR ; 
 int INT_KEYPAD ; 
 int INT_NOINIT ; 
 int INT_PWM1 ; 
 int INT_ROTATOR ; 
 int /*<<< orphan*/  LM8323_CMD_READ_INT ; 
 int LM8323_NUM_PWMS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lm8323_configure (struct lm8323_chip*) ; 
 int /*<<< orphan*/  lm8323_process_error (struct lm8323_chip*) ; 
 int lm8323_read (struct lm8323_chip*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_keys (struct lm8323_chip*) ; 
 int /*<<< orphan*/  pwm_done (int /*<<< orphan*/ *) ; 
 struct lm8323_chip* work_to_lm8323 (struct work_struct*) ; 

__attribute__((used)) static void lm8323_work(struct work_struct *work)
{
	struct lm8323_chip *lm = work_to_lm8323(work);
	u8 ints;
	int i;

	mutex_lock(&lm->lock);

	while ((lm8323_read(lm, LM8323_CMD_READ_INT, &ints, 1) == 1) && ints) {
		if (likely(ints & INT_KEYPAD))
			process_keys(lm);
		if (ints & INT_ROTATOR) {
			/* We don't currently support the rotator. */
			dev_vdbg(&lm->client->dev, "rotator fired\n");
		}
		if (ints & INT_ERROR) {
			dev_vdbg(&lm->client->dev, "error!\n");
			lm8323_process_error(lm);
		}
		if (ints & INT_NOINIT) {
			dev_err(&lm->client->dev, "chip lost config; "
						  "reinitialising\n");
			lm8323_configure(lm);
		}
		for (i = 0; i < LM8323_NUM_PWMS; i++) {
			if (ints & (1 << (INT_PWM1 + i))) {
				dev_vdbg(&lm->client->dev,
					 "pwm%d engine completed\n", i);
				pwm_done(&lm->pwm[i]);
			}
		}
	}

	mutex_unlock(&lm->lock);
}