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
struct xfrm_state_afinfo {struct xfrm_mode** mode_map; } ;
struct xfrm_mode {size_t encap; TYPE_1__* afinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENOENT ; 
 size_t XFRM_MODE_MAX ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct xfrm_state_afinfo* xfrm_state_lock_afinfo (int) ; 
 int /*<<< orphan*/  xfrm_state_unlock_afinfo (struct xfrm_state_afinfo*) ; 

int xfrm_unregister_mode(struct xfrm_mode *mode, int family)
{
	struct xfrm_state_afinfo *afinfo;
	struct xfrm_mode **modemap;
	int err;

	if (unlikely(mode->encap >= XFRM_MODE_MAX))
		return -EINVAL;

	afinfo = xfrm_state_lock_afinfo(family);
	if (unlikely(afinfo == NULL))
		return -EAFNOSUPPORT;

	err = -ENOENT;
	modemap = afinfo->mode_map;
	if (likely(modemap[mode->encap] == mode)) {
		modemap[mode->encap] = NULL;
		module_put(mode->afinfo->owner);
		err = 0;
	}

	xfrm_state_unlock_afinfo(afinfo);
	return err;
}