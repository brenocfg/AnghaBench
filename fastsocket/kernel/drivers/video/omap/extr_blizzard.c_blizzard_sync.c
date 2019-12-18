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
struct completion {int dummy; } ;
struct TYPE_2__ {struct completion* sync; } ;
struct blizzard_request {int /*<<< orphan*/  entry; TYPE_1__ par; int /*<<< orphan*/ * complete; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 struct blizzard_request* alloc_req () ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  req_list ; 
 int /*<<< orphan*/  submit_req_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_handler ; 
 int /*<<< orphan*/  wait_for_completion (struct completion*) ; 

__attribute__((used)) static void blizzard_sync(void)
{
	LIST_HEAD(req_list);
	struct blizzard_request *req;
	struct completion comp;

	req = alloc_req();

	req->handler = sync_handler;
	req->complete = NULL;
	init_completion(&comp);
	req->par.sync = &comp;

	list_add(&req->entry, &req_list);
	submit_req_list(&req_list);

	wait_for_completion(&comp);
}