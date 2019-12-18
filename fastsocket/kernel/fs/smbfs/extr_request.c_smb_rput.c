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
struct smb_request {int /*<<< orphan*/  rq_queue; int /*<<< orphan*/  rq_count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_free_request (struct smb_request*) ; 

void smb_rput(struct smb_request *req)
{
	if (atomic_dec_and_test(&req->rq_count)) {
		list_del_init(&req->rq_queue);
		smb_free_request(req);
	}
}