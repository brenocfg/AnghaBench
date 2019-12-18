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
typedef  int u32 ;
struct mISDN_ctrl_req {int op; int p1; int p2; } ;
struct TYPE_3__ {TYPE_2__* peer; } ;
struct dsp {TYPE_1__ ch; } ;
typedef  int /*<<< orphan*/  cq ;
struct TYPE_4__ {int /*<<< orphan*/  (* ctrl ) (TYPE_2__*,int /*<<< orphan*/ ,struct mISDN_ctrl_req*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_CHANNEL ; 
 int /*<<< orphan*/  memset (struct mISDN_ctrl_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,struct mISDN_ctrl_req*) ; 

__attribute__((used)) static void
dsp_cmx_hw_message(struct dsp *dsp, u32 message, u32 param1, u32 param2,
    u32 param3, u32 param4)
{
	struct mISDN_ctrl_req cq;

	memset(&cq, 0, sizeof(cq));
	cq.op = message;
	cq.p1 = param1 | (param2 << 8);
	cq.p2 = param3 | (param4 << 8);
	if (dsp->ch.peer)
		dsp->ch.peer->ctrl(dsp->ch.peer, CONTROL_CHANNEL, &cq);
}