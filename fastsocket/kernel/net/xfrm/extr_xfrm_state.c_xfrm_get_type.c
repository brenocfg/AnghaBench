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
typedef  size_t u8 ;
struct xfrm_type {int /*<<< orphan*/  owner; } ;
struct xfrm_state_afinfo {struct xfrm_type** type_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  request_module (char*,unsigned short,size_t) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct xfrm_state_afinfo* xfrm_state_get_afinfo (unsigned short) ; 
 int /*<<< orphan*/  xfrm_state_put_afinfo (struct xfrm_state_afinfo*) ; 

__attribute__((used)) static const struct xfrm_type *xfrm_get_type(u8 proto, unsigned short family)
{
	struct xfrm_state_afinfo *afinfo;
	const struct xfrm_type **typemap;
	const struct xfrm_type *type;
	int modload_attempted = 0;

retry:
	afinfo = xfrm_state_get_afinfo(family);
	if (unlikely(afinfo == NULL))
		return NULL;
	typemap = afinfo->type_map;

	type = typemap[proto];
	if (unlikely(type && !try_module_get(type->owner)))
		type = NULL;
	if (!type && !modload_attempted) {
		xfrm_state_put_afinfo(afinfo);
		request_module("xfrm-type-%d-%d", family, proto);
		modload_attempted = 1;
		goto retry;
	}

	xfrm_state_put_afinfo(afinfo);
	return type;
}