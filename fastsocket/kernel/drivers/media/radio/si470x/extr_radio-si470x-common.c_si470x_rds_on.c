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
struct si470x_device {int /*<<< orphan*/  lock; int /*<<< orphan*/ * registers; } ;

/* Variables and functions */
 size_t SYSCONFIG1 ; 
 int /*<<< orphan*/  SYSCONFIG1_RDS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si470x_set_register (struct si470x_device*,size_t) ; 

int si470x_rds_on(struct si470x_device *radio)
{
	int retval;

	/* sysconfig 1 */
	mutex_lock(&radio->lock);
	radio->registers[SYSCONFIG1] |= SYSCONFIG1_RDS;
	retval = si470x_set_register(radio, SYSCONFIG1);
	if (retval < 0)
		radio->registers[SYSCONFIG1] &= ~SYSCONFIG1_RDS;
	mutex_unlock(&radio->lock);

	return retval;
}