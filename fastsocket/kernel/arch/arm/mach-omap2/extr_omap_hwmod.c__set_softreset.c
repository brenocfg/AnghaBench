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
typedef  int /*<<< orphan*/  u32 ;
struct omap_hwmod {TYPE_1__* sysconfig; } ;
struct TYPE_2__ {int sysc_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int SYSC_HAS_SOFTRESET ; 
 int /*<<< orphan*/  SYSC_SOFTRESET_MASK ; 

__attribute__((used)) static int _set_softreset(struct omap_hwmod *oh, u32 *v)
{
	if (!oh->sysconfig ||
	    !(oh->sysconfig->sysc_flags & SYSC_HAS_SOFTRESET))
		return -EINVAL;

	*v |= SYSC_SOFTRESET_MASK;

	return 0;
}