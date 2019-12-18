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
struct ib_uobject {int /*<<< orphan*/  ref; struct ib_ucontext* context; } ;
struct ib_ucontext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_uverbs_idr_lock ; 
 struct ib_uobject* idr_find (struct idr*,int) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ib_uobject *__idr_get_uobj(struct idr *idr, int id,
					 struct ib_ucontext *context)
{
	struct ib_uobject *uobj;

	spin_lock(&ib_uverbs_idr_lock);
	uobj = idr_find(idr, id);
	if (uobj) {
		if (uobj->context == context)
			kref_get(&uobj->ref);
		else
			uobj = NULL;
	}
	spin_unlock(&ib_uverbs_idr_lock);

	return uobj;
}