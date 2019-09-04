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
struct waitq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pltrace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_held (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock_unlock (struct waitq*) ; 

void waitq_unlock(struct waitq *wq)
{
	assert(waitq_held(wq));
#if defined(__x86_64__)
	pltrace(TRUE);
#endif
	waitq_lock_unlock(wq);
}