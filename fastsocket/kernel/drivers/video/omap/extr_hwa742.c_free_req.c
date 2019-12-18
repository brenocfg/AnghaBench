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
struct hwa742_request {int flags; int /*<<< orphan*/  entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  req_lock; int /*<<< orphan*/  req_sema; int /*<<< orphan*/  free_req_list; } ;

/* Variables and functions */
 int REQ_FROM_IRQ_POOL ; 
 TYPE_1__ hwa742 ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void free_req(struct hwa742_request *req)
{
	unsigned long flags;

	spin_lock_irqsave(&hwa742.req_lock, flags);

	list_del(&req->entry);
	list_add(&req->entry, &hwa742.free_req_list);
	if (!(req->flags & REQ_FROM_IRQ_POOL))
		up(&hwa742.req_sema);

	spin_unlock_irqrestore(&hwa742.req_lock, flags);
}