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
struct pending_request {int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct pending_request* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pending_request *__alloc_pending_request(gfp_t flags)
{
	struct pending_request *req;

	req = kzalloc(sizeof(*req), flags);
	if (req)
		INIT_LIST_HEAD(&req->list);

	return req;
}