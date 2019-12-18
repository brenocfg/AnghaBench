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
struct c2_vq_req {int /*<<< orphan*/  reply_ready; int /*<<< orphan*/  wait_object; } ;
struct c2_dev {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int vq_wait_for_reply(struct c2_dev *c2dev, struct c2_vq_req *req)
{
	if (!wait_event_timeout(req->wait_object,
				atomic_read(&req->reply_ready),
				60*HZ))
		return -ETIMEDOUT;

	return 0;
}