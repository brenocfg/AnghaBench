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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ml_timer_evaluate () ; 
 int timer_user_idle_level ; 

kern_return_t timer_set_user_idle_level(int ilevel) {
	boolean_t do_reeval = FALSE;

	if ((ilevel < 0) || (ilevel > 128))
		return KERN_INVALID_ARGUMENT;

	if (ilevel < timer_user_idle_level) {
		do_reeval = TRUE;
	}

	timer_user_idle_level = ilevel;

	if (do_reeval)
		ml_timer_evaluate();

	return KERN_SUCCESS;
}