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
struct TYPE_4__ {int /*<<< orphan*/  flag; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* layer ) (struct PStack*,int,void*) ;} ;
struct PStack {TYPE_2__ l2; TYPE_1__ ma; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_L3_INIT ; 
 int INDICATION ; 
 int MDL_ERROR ; 
 int /*<<< orphan*/  establishlink (struct FsmInst*) ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,void*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nrerrorrecovery(struct FsmInst *fi)
{
	struct PStack *st = fi->userdata;

	st->ma.layer(st, MDL_ERROR | INDICATION, (void *) 'J');
	establishlink(fi);
	test_and_clear_bit(FLG_L3_INIT, &st->l2.flag);
}