#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfrm_tmpl {scalar_t__ mode; scalar_t__ optional; } ;
struct sec_path {int len; TYPE_2__** xvec; } ;
struct TYPE_3__ {scalar_t__ mode; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 scalar_t__ XFRM_MODE_TRANSPORT ; 
 scalar_t__ xfrm_state_ok (struct xfrm_tmpl*,TYPE_2__*,unsigned short) ; 

__attribute__((used)) static inline int
xfrm_policy_ok(struct xfrm_tmpl *tmpl, struct sec_path *sp, int start,
	       unsigned short family)
{
	int idx = start;

	if (tmpl->optional) {
		if (tmpl->mode == XFRM_MODE_TRANSPORT)
			return start;
	} else
		start = -1;
	for (; idx < sp->len; idx++) {
		if (xfrm_state_ok(tmpl, sp->xvec[idx], family))
			return ++idx;
		if (sp->xvec[idx]->props.mode != XFRM_MODE_TRANSPORT) {
			if (start == -1)
				start = -2-idx;
			break;
		}
	}
	return start;
}