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
struct mutex {int dummy; } ;
struct idr {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ID_MASK ; 
 int idr_get_new (struct idr*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ idr_pre_get (struct idr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int get_idr(struct idr *idr, struct mutex *lock, int *id)
{
	int err;

      again:
	if (unlikely(idr_pre_get(idr, GFP_KERNEL) == 0))
		return -ENOMEM;

	if (lock)
		mutex_lock(lock);
	err = idr_get_new(idr, NULL, id);
	if (lock)
		mutex_unlock(lock);
	if (unlikely(err == -EAGAIN))
		goto again;
	else if (unlikely(err))
		return err;

	*id = *id & MAX_ID_MASK;
	return 0;
}