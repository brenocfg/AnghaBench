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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct omap_hwmod {TYPE_1__* sysconfig; } ;
struct TYPE_2__ {int sysc_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int SYSC_HAS_MIDLEMODE ; 
 int SYSC_MIDLEMODE_MASK ; 
 int SYSC_MIDLEMODE_SHIFT ; 
 int __ffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _set_master_standbymode(struct omap_hwmod *oh, u8 standbymode,
				   u32 *v)
{
	if (!oh->sysconfig ||
	    !(oh->sysconfig->sysc_flags & SYSC_HAS_MIDLEMODE))
		return -EINVAL;

	*v &= ~SYSC_MIDLEMODE_MASK;
	*v |= __ffs(standbymode) << SYSC_MIDLEMODE_SHIFT;

	return 0;
}