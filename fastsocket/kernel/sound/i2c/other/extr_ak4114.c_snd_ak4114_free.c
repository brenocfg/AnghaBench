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
struct ak4114 {int init; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  kfree (struct ak4114*) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void snd_ak4114_free(struct ak4114 *chip)
{
	chip->init = 1;	/* don't schedule new work */
	mb();
	cancel_delayed_work(&chip->work);
	flush_scheduled_work();
	kfree(chip);
}