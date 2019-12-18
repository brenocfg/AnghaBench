#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int* Stat; } ;
struct vx_core {int /*<<< orphan*/  lock; TYPE_1__ irq_rmh; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TEST_IT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vx_init_rmh (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int vx_send_msg_nolock (struct vx_core*,TYPE_1__*) ; 

__attribute__((used)) static int vx_test_irq_src(struct vx_core *chip, unsigned int *ret)
{
	int err;

	vx_init_rmh(&chip->irq_rmh, CMD_TEST_IT);
	spin_lock(&chip->lock);
	err = vx_send_msg_nolock(chip, &chip->irq_rmh);
	if (err < 0)
		*ret = 0;
	else
		*ret = chip->irq_rmh.Stat[0];
	spin_unlock(&chip->lock);
	return err;
}