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
typedef  int /*<<< orphan*/  u32 ;
struct maple_device {TYPE_1__* mq; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {size_t length; int /*<<< orphan*/  list; void* sendbuf; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maple_waitq ; 
 int /*<<< orphan*/  maple_wlist_lock ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int maple_add_packet(struct maple_device *mdev, u32 function, u32 command,
	size_t length, void *data)
{
	int ret = 0;
	void *sendbuf = NULL;

	if (length) {
		sendbuf = kzalloc(length * 4, GFP_KERNEL);
		if (!sendbuf) {
			ret = -ENOMEM;
			goto out;
		}
		((__be32 *)sendbuf)[0] = cpu_to_be32(function);
	}

	mdev->mq->command = command;
	mdev->mq->length = length;
	if (length > 1)
		memcpy(sendbuf + 4, data, (length - 1) * 4);
	mdev->mq->sendbuf = sendbuf;

	mutex_lock(&maple_wlist_lock);
	list_add_tail(&mdev->mq->list, &maple_waitq);
	mutex_unlock(&maple_wlist_lock);
out:
	return ret;
}