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
struct xfrm_usersa_info {int /*<<< orphan*/  seq; int /*<<< orphan*/  flags; int /*<<< orphan*/  family; int /*<<< orphan*/  reqid; int /*<<< orphan*/  replay_window; int /*<<< orphan*/  mode; int /*<<< orphan*/  saddr; int /*<<< orphan*/  stats; int /*<<< orphan*/  curlft; int /*<<< orphan*/  lft; int /*<<< orphan*/  sel; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  family; int /*<<< orphan*/  reqid; int /*<<< orphan*/  replay_window; int /*<<< orphan*/  mode; int /*<<< orphan*/  saddr; } ;
struct xfrm_state {TYPE_2__ km; TYPE_1__ props; int /*<<< orphan*/  stats; int /*<<< orphan*/  curlft; int /*<<< orphan*/  lft; int /*<<< orphan*/  sel; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct xfrm_usersa_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void copy_to_user_state(struct xfrm_state *x, struct xfrm_usersa_info *p)
{
	memset(p, 0, sizeof(*p));
	memcpy(&p->id, &x->id, sizeof(p->id));
	memcpy(&p->sel, &x->sel, sizeof(p->sel));
	memcpy(&p->lft, &x->lft, sizeof(p->lft));
	memcpy(&p->curlft, &x->curlft, sizeof(p->curlft));
	memcpy(&p->stats, &x->stats, sizeof(p->stats));
	memcpy(&p->saddr, &x->props.saddr, sizeof(p->saddr));
	p->mode = x->props.mode;
	p->replay_window = x->props.replay_window;
	p->reqid = x->props.reqid;
	p->family = x->props.family;
	p->flags = x->props.flags;
	p->seq = x->km.seq;
}