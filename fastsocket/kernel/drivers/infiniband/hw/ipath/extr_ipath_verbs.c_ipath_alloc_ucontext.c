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
struct ib_ucontext {int dummy; } ;
struct ipath_ucontext {struct ib_ucontext ibucontext; } ;
struct ib_udata {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_ucontext* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ipath_ucontext* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_ucontext *ipath_alloc_ucontext(struct ib_device *ibdev,
						struct ib_udata *udata)
{
	struct ipath_ucontext *context;
	struct ib_ucontext *ret;

	context = kmalloc(sizeof *context, GFP_KERNEL);
	if (!context) {
		ret = ERR_PTR(-ENOMEM);
		goto bail;
	}

	ret = &context->ibucontext;

bail:
	return ret;
}