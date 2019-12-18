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
struct omap_hwmod {int /*<<< orphan*/  _int_flags; TYPE_1__* sysconfig; int /*<<< orphan*/  _sysc_cache; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  sysc_offs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _HWMOD_SYSCONFIG_LOADED ; 
 int /*<<< orphan*/  omap_hwmod_readl (struct omap_hwmod*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _update_sysc_cache(struct omap_hwmod *oh)
{
	if (!oh->sysconfig) {
		WARN(!oh->sysconfig, "omap_hwmod: %s: cannot read "
		     "OCP_SYSCONFIG: not defined on hwmod\n", oh->name);
		return -EINVAL;
	}

	/* XXX ensure module interface clock is up */

	oh->_sysc_cache = omap_hwmod_readl(oh, oh->sysconfig->sysc_offs);

	oh->_int_flags |= _HWMOD_SYSCONFIG_LOADED;

	return 0;
}