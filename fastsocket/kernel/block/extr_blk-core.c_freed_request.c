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
struct request_list {int /*<<< orphan*/ * starved; int /*<<< orphan*/  elvpriv; int /*<<< orphan*/ * count; } ;
struct request_queue {struct request_list rq; } ;

/* Variables and functions */
 unsigned int REQ_ELVPRIV ; 
 int /*<<< orphan*/  __freed_request (struct request_queue*,int) ; 
 int rw_is_sync (unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freed_request(struct request_queue *q, unsigned int flags)
{
	struct request_list *rl = &q->rq;
	int sync = rw_is_sync(flags);

	rl->count[sync]--;
	if (flags & REQ_ELVPRIV)
		rl->elvpriv--;

	__freed_request(q, sync);

	if (unlikely(rl->starved[sync ^ 1]))
		__freed_request(q, sync ^ 1);
}