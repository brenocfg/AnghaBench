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
struct ecard_request {int /*<<< orphan*/  complete; int /*<<< orphan*/  (* fn ) (struct ecard_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 scalar_t__ ecard_init_mm () ; 
 int /*<<< orphan*/ * ecard_req ; 
 int /*<<< orphan*/  ecard_wait ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stub1 (struct ecard_request*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ecard_request* xchg (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ecard_task(void * unused)
{
	/*
	 * Allocate a mm.  We're not a lazy-TLB kernel task since we need
	 * to set page table entries where the user space would be.  Note
	 * that this also creates the page tables.  Failure is not an
	 * option here.
	 */
	if (ecard_init_mm())
		panic("kecardd: unable to alloc mm\n");

	while (1) {
		struct ecard_request *req;

		wait_event_interruptible(ecard_wait, ecard_req != NULL);

		req = xchg(&ecard_req, NULL);
		if (req != NULL) {
			req->fn(req);
			complete(req->complete);
		}
	}
}