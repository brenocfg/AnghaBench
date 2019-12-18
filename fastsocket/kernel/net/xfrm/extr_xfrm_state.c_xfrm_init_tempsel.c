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
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct xfrm_tmpl {int dummy; } ;
struct xfrm_state_afinfo {int /*<<< orphan*/  (* init_tempsel ) (struct xfrm_state*,struct flowi*,struct xfrm_tmpl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct xfrm_state {int dummy; } ;
struct flowi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct xfrm_state*,struct flowi*,struct xfrm_tmpl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct xfrm_state_afinfo* xfrm_state_get_afinfo (unsigned short) ; 
 int /*<<< orphan*/  xfrm_state_put_afinfo (struct xfrm_state_afinfo*) ; 

__attribute__((used)) static int
xfrm_init_tempsel(struct xfrm_state *x, struct flowi *fl,
		  struct xfrm_tmpl *tmpl,
		  xfrm_address_t *daddr, xfrm_address_t *saddr,
		  unsigned short family)
{
	struct xfrm_state_afinfo *afinfo = xfrm_state_get_afinfo(family);
	if (!afinfo)
		return -1;
	afinfo->init_tempsel(x, fl, tmpl, daddr, saddr);
	xfrm_state_put_afinfo(afinfo);
	return 0;
}