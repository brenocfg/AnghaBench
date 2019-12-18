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
typedef  int /*<<< orphan*/  wr ;
struct TYPE_3__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  bind_info; struct ib_mw* mw; } ;
struct TYPE_4__ {TYPE_1__ bind_mw; } ;
struct ib_send_wr {TYPE_2__ wr; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  opcode; } ;
struct ib_qp {int dummy; } ;
struct ib_mw_bind {int /*<<< orphan*/  bind_info; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  wr_id; } ;
struct ib_mw {int /*<<< orphan*/  rkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WR_BIND_MW ; 
 int /*<<< orphan*/  ib_inc_rkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_send_wr*,int /*<<< orphan*/ ,int) ; 
 int mlx4_ib_post_send (struct ib_qp*,struct ib_send_wr*,struct ib_send_wr**) ; 

int mlx4_ib_bind_mw(struct ib_qp *qp, struct ib_mw *mw,
		    struct ib_mw_bind *mw_bind)
{
	struct ib_send_wr  wr;
	struct ib_send_wr *bad_wr;
	int ret;

	memset(&wr, 0, sizeof(wr));
	wr.opcode               = IB_WR_BIND_MW;
	wr.wr_id                = mw_bind->wr_id;
	wr.send_flags           = mw_bind->send_flags;
	wr.wr.bind_mw.mw        = mw;
	wr.wr.bind_mw.bind_info = mw_bind->bind_info;
	wr.wr.bind_mw.rkey      = ib_inc_rkey(mw->rkey);

	ret = mlx4_ib_post_send(qp, &wr, &bad_wr);
	if (!ret)
		mw->rkey = wr.wr.bind_mw.rkey;

	return ret;
}