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
struct st5481_adapter {int /*<<< orphan*/  timer; } ;
struct FsmInst {struct st5481_adapter* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_L1L2 (struct st5481_adapter*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INDICATION ; 
 int PH_ACTIVATE ; 
 int /*<<< orphan*/  ST_L1_F7 ; 
 int /*<<< orphan*/  ph_connect (struct st5481_adapter*) ; 

__attribute__((used)) static void
l1_go_f7(struct FsmInst *fi, int event, void *arg)
{
	struct st5481_adapter *adapter = fi->userdata;

	FsmDelTimer(&adapter->timer, 0);
	ph_connect(adapter);
	FsmChangeState(fi, ST_L1_F7);
	D_L1L2(adapter, PH_ACTIVATE | INDICATION, NULL);
}