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
struct xfrm_usersa_info {int flags; scalar_t__ family; int /*<<< orphan*/  saddr; int /*<<< orphan*/  reqid; int /*<<< orphan*/  replay_window; int /*<<< orphan*/  mode; int /*<<< orphan*/  lft; int /*<<< orphan*/  sel; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {scalar_t__ family; } ;
struct TYPE_3__ {int flags; TYPE_2__ saddr; scalar_t__ family; int /*<<< orphan*/  reqid; int /*<<< orphan*/  replay_window; int /*<<< orphan*/  mode; } ;
struct xfrm_state {TYPE_2__ sel; TYPE_1__ props; TYPE_2__ lft; TYPE_2__ id; } ;

/* Variables and functions */
 int XFRM_STATE_AF_UNSPEC ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void copy_from_user_state(struct xfrm_state *x, struct xfrm_usersa_info *p)
{
	memcpy(&x->id, &p->id, sizeof(x->id));
	memcpy(&x->sel, &p->sel, sizeof(x->sel));
	memcpy(&x->lft, &p->lft, sizeof(x->lft));
	x->props.mode = p->mode;
	x->props.replay_window = p->replay_window;
	x->props.reqid = p->reqid;
	x->props.family = p->family;
	memcpy(&x->props.saddr, &p->saddr, sizeof(x->props.saddr));
	x->props.flags = p->flags;

	if (!x->sel.family && !(p->flags & XFRM_STATE_AF_UNSPEC))
		x->sel.family = p->family;
}