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
struct xfrm_state_afinfo {int /*<<< orphan*/  owner; struct xfrm_mode** mode_map; } ;
struct xfrm_mode {size_t encap; struct xfrm_state_afinfo* afinfo; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 size_t XFRM_MODE_MAX ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct xfrm_state_afinfo* xfrm_state_lock_afinfo (int) ; 
 int /*<<< orphan*/  xfrm_state_unlock_afinfo (struct xfrm_state_afinfo*) ; 

int xfrm_register_mode(struct xfrm_mode *mode, int family)
{
	struct xfrm_state_afinfo *afinfo;
	struct xfrm_mode **modemap;
	int err;

	if (unlikely(mode->encap >= XFRM_MODE_MAX))
		return -EINVAL;

	afinfo = xfrm_state_lock_afinfo(family);
	if (unlikely(afinfo == NULL))
		return -EAFNOSUPPORT;

	err = -EEXIST;
	modemap = afinfo->mode_map;
	if (modemap[mode->encap])
		goto out;

	err = -ENOENT;
	if (!try_module_get(afinfo->owner))
		goto out;

	mode->afinfo = afinfo;
	modemap[mode->encap] = mode;
	err = 0;

out:
	xfrm_state_unlock_afinfo(afinfo);
	return err;
}