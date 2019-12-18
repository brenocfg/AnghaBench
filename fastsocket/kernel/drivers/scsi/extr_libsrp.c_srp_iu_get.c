#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct srp_target {TYPE_1__ iu_queue; } ;
struct iu_entry {scalar_t__ flags; int /*<<< orphan*/  ilist; struct srp_target* target; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_get (int /*<<< orphan*/ ,void*,int) ; 

struct iu_entry *srp_iu_get(struct srp_target *target)
{
	struct iu_entry *iue = NULL;

	kfifo_get(target->iu_queue.queue, (void *) &iue, sizeof(void *));
	if (!iue)
		return iue;
	iue->target = target;
	INIT_LIST_HEAD(&iue->ilist);
	iue->flags = 0;
	return iue;
}