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
struct ib_uobject {int /*<<< orphan*/  live; int /*<<< orphan*/  mutex; } ;
struct ib_ucontext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 struct ib_uobject* __idr_get_uobj (struct idr*,int,struct ib_ucontext*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_uobj_read (struct ib_uobject*) ; 

__attribute__((used)) static struct ib_uobject *idr_read_uobj(struct idr *idr, int id,
					struct ib_ucontext *context, int nested)
{
	struct ib_uobject *uobj;

	uobj = __idr_get_uobj(idr, id, context);
	if (!uobj)
		return NULL;

	if (nested)
		down_read_nested(&uobj->mutex, SINGLE_DEPTH_NESTING);
	else
		down_read(&uobj->mutex);
	if (!uobj->live) {
		put_uobj_read(uobj);
		return NULL;
	}

	return uobj;
}