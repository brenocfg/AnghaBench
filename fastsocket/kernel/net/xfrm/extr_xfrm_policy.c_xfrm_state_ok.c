#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ proto; scalar_t__ spi; } ;
struct xfrm_tmpl {unsigned short encap_family; scalar_t__ reqid; scalar_t__ mode; int aalgos; TYPE_2__ id; scalar_t__ allalgs; scalar_t__ optional; } ;
struct TYPE_6__ {scalar_t__ reqid; scalar_t__ mode; int aalgo; } ;
struct TYPE_4__ {scalar_t__ proto; scalar_t__ spi; } ;
struct xfrm_state {TYPE_3__ props; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSEC_PROTO_ANY ; 
 scalar_t__ XFRM_MODE_TRANSPORT ; 
 int /*<<< orphan*/  xfrm_id_proto_match (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ xfrm_state_addr_cmp (struct xfrm_tmpl*,struct xfrm_state*,unsigned short) ; 
 scalar_t__ xfrm_state_kern (struct xfrm_state*) ; 

__attribute__((used)) static inline int
xfrm_state_ok(struct xfrm_tmpl *tmpl, struct xfrm_state *x,
	      unsigned short family)
{
	if (xfrm_state_kern(x))
		return tmpl->optional && !xfrm_state_addr_cmp(tmpl, x, tmpl->encap_family);
	return	x->id.proto == tmpl->id.proto &&
		(x->id.spi == tmpl->id.spi || !tmpl->id.spi) &&
		(x->props.reqid == tmpl->reqid || !tmpl->reqid) &&
		x->props.mode == tmpl->mode &&
		(tmpl->allalgs || (tmpl->aalgos & (1<<x->props.aalgo)) ||
		 !(xfrm_id_proto_match(tmpl->id.proto, IPSEC_PROTO_ANY))) &&
		!(x->props.mode != XFRM_MODE_TRANSPORT &&
		  xfrm_state_addr_cmp(tmpl, x, family));
}