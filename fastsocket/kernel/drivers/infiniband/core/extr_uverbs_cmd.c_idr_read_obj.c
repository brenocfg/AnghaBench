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
struct ib_uobject {void* object; } ;
struct ib_ucontext {int dummy; } ;

/* Variables and functions */
 struct ib_uobject* idr_read_uobj (struct idr*,int,struct ib_ucontext*,int) ; 

__attribute__((used)) static void *idr_read_obj(struct idr *idr, int id, struct ib_ucontext *context,
			  int nested)
{
	struct ib_uobject *uobj;

	uobj = idr_read_uobj(idr, id, context, nested);
	return uobj ? uobj->object : NULL;
}