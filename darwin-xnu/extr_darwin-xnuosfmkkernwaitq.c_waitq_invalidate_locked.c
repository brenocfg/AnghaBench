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
struct waitq {scalar_t__ waitq_isvalid; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_held (struct waitq*) ; 
 int /*<<< orphan*/  waitq_is_valid (struct waitq*) ; 

void waitq_invalidate_locked(struct waitq *waitq)
{
	assert(waitq_held(waitq));
	assert(waitq_is_valid(waitq));
	waitq->waitq_isvalid = 0;
}