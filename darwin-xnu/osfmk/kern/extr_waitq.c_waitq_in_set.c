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
struct waitq_link {int dummy; } ;
struct waitq {scalar_t__ waitq_set_id; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 struct waitq_link* wql_get_link (scalar_t__) ; 
 int /*<<< orphan*/  wql_put_link (struct waitq_link*) ; 

boolean_t waitq_in_set(struct waitq *waitq)
{
	struct waitq_link *link;
	boolean_t inset = FALSE;

	if (waitq_irq_safe(waitq))
		return FALSE;

	waitq_lock(waitq);

	if (!waitq->waitq_set_id)
		goto out_unlock;

	link = wql_get_link(waitq->waitq_set_id);
	if (link) {
		/* if we get here, the waitq is in _at_least_one_ set */
		inset = TRUE;
		wql_put_link(link);
	} else {
		/* we can just optimize this for next time */
		waitq->waitq_set_id = 0;
	}

out_unlock:
	waitq_unlock(waitq);
	return inset;
}