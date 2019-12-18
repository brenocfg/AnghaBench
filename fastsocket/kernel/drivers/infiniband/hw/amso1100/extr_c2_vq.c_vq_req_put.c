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
struct c2_vq_req {scalar_t__ reply_msg; int /*<<< orphan*/  refcnt; } ;
struct c2_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_repbuf_free (struct c2_dev*,void*) ; 

void vq_req_put(struct c2_dev *c2dev, struct c2_vq_req *r)
{
	if (atomic_dec_and_test(&r->refcnt)) {
		if (r->reply_msg != 0)
			vq_repbuf_free(c2dev,
				       (void *) (unsigned long) r->reply_msg);
		kfree(r);
	}
}