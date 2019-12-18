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
struct idr {int dummy; } ;
struct ib_uobject {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ib_uverbs_idr_lock ; 
 int idr_get_new (struct idr*,struct ib_uobject*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_pre_get (struct idr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idr_add_uobj(struct idr *idr, struct ib_uobject *uobj)
{
	int ret;

retry:
	if (!idr_pre_get(idr, GFP_KERNEL))
		return -ENOMEM;

	spin_lock(&ib_uverbs_idr_lock);
	ret = idr_get_new(idr, uobj, &uobj->id);
	spin_unlock(&ib_uverbs_idr_lock);

	if (ret == -EAGAIN)
		goto retry;

	return ret;
}