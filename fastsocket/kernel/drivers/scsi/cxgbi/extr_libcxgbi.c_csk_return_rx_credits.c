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
typedef  scalar_t__ u32 ;
struct cxgbi_sock {scalar_t__ state; scalar_t__ copied_seq; scalar_t__ rcv_wup; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; struct cxgbi_device* cdev; } ;
struct cxgbi_device {scalar_t__ rx_credit_thres; scalar_t__ rcv_win; scalar_t__ (* csk_send_rx_credits ) (struct cxgbi_sock*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ CTP_ESTABLISHED ; 
 int CXGBI_DBG_PDU_RX ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (struct cxgbi_sock*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void csk_return_rx_credits(struct cxgbi_sock *csk, int copied)
{
	struct cxgbi_device *cdev = csk->cdev;
	int must_send;
	u32 credits;

	log_debug(1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p,%u,0x%lu,%u, seq %u, wup %u, thre %u, %u.\n",
		csk, csk->state, csk->flags, csk->tid, csk->copied_seq,
		csk->rcv_wup, cdev->rx_credit_thres,
		cdev->rcv_win);

	if (csk->state != CTP_ESTABLISHED)
		return;

	credits = csk->copied_seq - csk->rcv_wup;
	if (unlikely(!credits))
		return;
	if (unlikely(cdev->rx_credit_thres == 0))
		return;

	must_send = credits + 16384 >= cdev->rcv_win;
	if (must_send || credits >= cdev->rx_credit_thres)
		csk->rcv_wup += cdev->csk_send_rx_credits(csk, credits);
}