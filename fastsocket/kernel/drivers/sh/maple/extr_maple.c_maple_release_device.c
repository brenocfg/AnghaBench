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
struct mapleq {int /*<<< orphan*/  recvbuf; struct mapleq* mq; } ;
struct maple_device {int /*<<< orphan*/  recvbuf; struct maple_device* mq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mapleq*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maple_queue_cache ; 
 struct mapleq* to_maple_dev (struct device*) ; 

__attribute__((used)) static void maple_release_device(struct device *dev)
{
	struct maple_device *mdev;
	struct mapleq *mq;

	mdev = to_maple_dev(dev);
	mq = mdev->mq;
	kmem_cache_free(maple_queue_cache, mq->recvbuf);
	kfree(mq);
	kfree(mdev);
}