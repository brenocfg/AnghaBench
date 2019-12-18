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
struct c2_vq_req {int /*<<< orphan*/  reply_ready; int /*<<< orphan*/  refcnt; int /*<<< orphan*/ * qp; int /*<<< orphan*/ * cm_id; scalar_t__ event; scalar_t__ reply_msg; int /*<<< orphan*/  wait_object; } ;
struct c2_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct c2_vq_req* kmalloc (int,int /*<<< orphan*/ ) ; 

struct c2_vq_req *vq_req_alloc(struct c2_dev *c2dev)
{
	struct c2_vq_req *r;

	r = kmalloc(sizeof(struct c2_vq_req), GFP_KERNEL);
	if (r) {
		init_waitqueue_head(&r->wait_object);
		r->reply_msg = 0;
		r->event = 0;
		r->cm_id = NULL;
		r->qp = NULL;
		atomic_set(&r->refcnt, 1);
		atomic_set(&r->reply_ready, 0);
	}
	return r;
}