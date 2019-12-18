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
struct TYPE_3__ {int /*<<< orphan*/  rll_lock; int /*<<< orphan*/ * rll_writer; int /*<<< orphan*/  rll_cv; scalar_t__ rll_readers; } ;
typedef  TYPE_1__ rll_t ;
typedef  scalar_t__ rl_type_t ;

/* Variables and functions */
 scalar_t__ RL_READER ; 
 int /*<<< orphan*/ * curthread ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ztest_rll_lock(rll_t *rll, rl_type_t type)
{
	mutex_enter(&rll->rll_lock);

	if (type == RL_READER) {
		while (rll->rll_writer != NULL)
			cv_wait(&rll->rll_cv, &rll->rll_lock);
		rll->rll_readers++;
	} else {
		while (rll->rll_writer != NULL || rll->rll_readers)
			cv_wait(&rll->rll_cv, &rll->rll_lock);
		rll->rll_writer = curthread;
	}

	mutex_exit(&rll->rll_lock);
}