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
struct ib_pd {int /*<<< orphan*/  usecnt; int /*<<< orphan*/ * uobject; struct ib_device* device; } ;
struct ib_device {struct ib_pd* (* alloc_pd ) (struct ib_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct ib_pd*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ib_pd* stub1 (struct ib_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct ib_pd *ib_alloc_pd(struct ib_device *device)
{
	struct ib_pd *pd;

	pd = device->alloc_pd(device, NULL, NULL);

	if (!IS_ERR(pd)) {
		pd->device  = device;
		pd->uobject = NULL;
		atomic_set(&pd->usecnt, 0);
	}

	return pd;
}