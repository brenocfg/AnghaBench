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
struct ib_pd {int /*<<< orphan*/  usecnt; TYPE_1__* device; } ;
struct ib_mw {int type; int /*<<< orphan*/ * uobject; struct ib_pd* pd; TYPE_1__* device; } ;
typedef  enum ib_mw_type { ____Placeholder_ib_mw_type } ib_mw_type ;
struct TYPE_2__ {struct ib_mw* (* alloc_mw ) (struct ib_pd*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 struct ib_mw* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct ib_mw*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct ib_mw* stub1 (struct ib_pd*,int) ; 

struct ib_mw *ib_alloc_mw(struct ib_pd *pd, enum ib_mw_type type)
{
	struct ib_mw *mw;

	if (!pd->device->alloc_mw)
		return ERR_PTR(-ENOSYS);

	mw = pd->device->alloc_mw(pd, type);
	if (!IS_ERR(mw)) {
		mw->device  = pd->device;
		mw->pd      = pd;
		mw->uobject = NULL;
		mw->type    = type;
		atomic_inc(&pd->usecnt);
	}

	return mw;
}