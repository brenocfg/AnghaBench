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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ mp_call_queue_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline boolean_t
mp_call_head_lock(mp_call_queue_t *cqp)
{
	boolean_t	intrs_enabled;

	intrs_enabled = ml_set_interrupts_enabled(FALSE);
	simple_lock(&cqp->lock);

	return intrs_enabled;
}