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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ucc_geth_private {TYPE_3__* p_rx_glbl_pram; TYPE_2__* ug_info; struct ucc_fast_private* uccf; } ;
struct ucc_fast_private {int stopped_rx; } ;
struct TYPE_6__ {int /*<<< orphan*/  rxgstpack; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucc_num; } ;
struct TYPE_5__ {TYPE_1__ uf_info; } ;

/* Variables and functions */
 int GRACEFUL_STOP_ACKNOWLEDGE_RX ; 
 int /*<<< orphan*/  QE_CR_PROTOCOL_ETHERNET ; 
 int /*<<< orphan*/  QE_GRACEFUL_STOP_RX ; 
 int in_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qe_issue_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucc_fast_get_qe_cr_subblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ugeth_graceful_stop_rx(struct ucc_geth_private *ugeth)
{
	struct ucc_fast_private *uccf;
	u32 cecr_subblock;
	u8 temp;
	int i = 10;

	uccf = ugeth->uccf;

	/* Clear acknowledge bit */
	temp = in_8(&ugeth->p_rx_glbl_pram->rxgstpack);
	temp &= ~GRACEFUL_STOP_ACKNOWLEDGE_RX;
	out_8(&ugeth->p_rx_glbl_pram->rxgstpack, temp);

	/* Keep issuing command and checking acknowledge bit until
	it is asserted, according to spec */
	do {
		/* Issue host command */
		cecr_subblock =
		    ucc_fast_get_qe_cr_subblock(ugeth->ug_info->uf_info.
						ucc_num);
		qe_issue_cmd(QE_GRACEFUL_STOP_RX, cecr_subblock,
			     QE_CR_PROTOCOL_ETHERNET, 0);
		msleep(10);
		temp = in_8(&ugeth->p_rx_glbl_pram->rxgstpack);
	} while (!(temp & GRACEFUL_STOP_ACKNOWLEDGE_RX) && --i);

	uccf->stopped_rx = 1;

	return 0;
}