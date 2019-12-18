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
struct ak4114 {int init; int /*<<< orphan*/  work; scalar_t__* kctls; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ak4114_init_regs (struct ak4114*) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

void snd_ak4114_reinit(struct ak4114 *chip)
{
	chip->init = 1;
	mb();
	flush_scheduled_work();
	ak4114_init_regs(chip);
	/* bring up statistics / event queing */
	chip->init = 0;
	if (chip->kctls[0])
		schedule_delayed_work(&chip->work, HZ / 10);
}