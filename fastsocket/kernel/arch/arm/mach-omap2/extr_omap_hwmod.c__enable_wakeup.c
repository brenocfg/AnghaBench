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
struct omap_hwmod {int /*<<< orphan*/  _int_flags; int /*<<< orphan*/  _sysc_cache; TYPE_1__* sysconfig; } ;
struct TYPE_2__ {int sysc_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SYSC_ENAWAKEUP_MASK ; 
 int SYSC_HAS_ENAWAKEUP ; 
 int /*<<< orphan*/  _HWMOD_WAKEUP_ENABLED ; 
 int /*<<< orphan*/  _write_sysconfig (int /*<<< orphan*/ ,struct omap_hwmod*) ; 

__attribute__((used)) static int _enable_wakeup(struct omap_hwmod *oh)
{
	u32 v;

	if (!oh->sysconfig ||
	    !(oh->sysconfig->sysc_flags & SYSC_HAS_ENAWAKEUP))
		return -EINVAL;

	v = oh->_sysc_cache;
	v |= SYSC_ENAWAKEUP_MASK;
	_write_sysconfig(v, oh);

	/* XXX test pwrdm_get_wken for this hwmod's subsystem */

	oh->_int_flags |= _HWMOD_WAKEUP_ENABLED;

	return 0;
}