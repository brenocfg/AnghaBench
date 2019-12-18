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
struct ib_pd {TYPE_1__* device; int /*<<< orphan*/  usecnt; } ;
struct TYPE_2__ {int (* dealloc_pd ) (struct ib_pd*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int stub1 (struct ib_pd*) ; 

int ib_dealloc_pd(struct ib_pd *pd)
{
	if (atomic_read(&pd->usecnt))
		return -EBUSY;

	return pd->device->dealloc_pd(pd);
}