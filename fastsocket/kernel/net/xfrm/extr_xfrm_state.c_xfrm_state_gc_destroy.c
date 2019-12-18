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
struct xfrm_state {TYPE_1__* type; scalar_t__ outer_mode; scalar_t__ inner_mode_iaf; scalar_t__ inner_mode; struct xfrm_state* coaddr; struct xfrm_state* encap; struct xfrm_state* calg; struct xfrm_state* ealg; struct xfrm_state* aalg; int /*<<< orphan*/  rtimer; int /*<<< orphan*/  timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destructor ) (struct xfrm_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct xfrm_state*) ; 
 int /*<<< orphan*/  security_xfrm_state_free (struct xfrm_state*) ; 
 int /*<<< orphan*/  stub1 (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_put_mode (scalar_t__) ; 
 int /*<<< orphan*/  xfrm_put_type (TYPE_1__*) ; 

__attribute__((used)) static void xfrm_state_gc_destroy(struct xfrm_state *x)
{
	del_timer_sync(&x->timer);
	del_timer_sync(&x->rtimer);
	kfree(x->aalg);
	kfree(x->ealg);
	kfree(x->calg);
	kfree(x->encap);
	kfree(x->coaddr);
	if (x->inner_mode)
		xfrm_put_mode(x->inner_mode);
	if (x->inner_mode_iaf)
		xfrm_put_mode(x->inner_mode_iaf);
	if (x->outer_mode)
		xfrm_put_mode(x->outer_mode);
	if (x->type) {
		x->type->destructor(x);
		xfrm_put_type(x->type);
	}
	security_xfrm_state_free(x);
	kfree(x);
}