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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct rfcomm_session {int dummy; } ;
struct rfcomm_msc {int v24_sig; int /*<<< orphan*/  dlci; } ;
struct rfcomm_dlc {int remote_v24_sig; int /*<<< orphan*/  mscex; int /*<<< orphan*/  (* modem_status ) (struct rfcomm_dlc*,int) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  cfc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RFCOMM_MSCEX_RX ; 
 int /*<<< orphan*/  RFCOMM_MSCEX_TX ; 
 int /*<<< orphan*/  RFCOMM_TX_THROTTLED ; 
 int RFCOMM_V24_FC ; 
 int /*<<< orphan*/  __get_dlci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rfcomm_dlc* rfcomm_dlc_get (struct rfcomm_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_send_msc (struct rfcomm_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rfcomm_dlc*,int) ; 

__attribute__((used)) static int rfcomm_recv_msc(struct rfcomm_session *s, int cr, struct sk_buff *skb)
{
	struct rfcomm_msc *msc = (void *) skb->data;
	struct rfcomm_dlc *d;
	u8 dlci = __get_dlci(msc->dlci);

	BT_DBG("dlci %d cr %d v24 0x%x", dlci, cr, msc->v24_sig);

	d = rfcomm_dlc_get(s, dlci);
	if (!d)
		return 0;

	if (cr) {
		if (msc->v24_sig & RFCOMM_V24_FC && !d->cfc)
			set_bit(RFCOMM_TX_THROTTLED, &d->flags);
		else
			clear_bit(RFCOMM_TX_THROTTLED, &d->flags);

		rfcomm_dlc_lock(d);

		d->remote_v24_sig = msc->v24_sig;

		if (d->modem_status)
			d->modem_status(d, msc->v24_sig);

		rfcomm_dlc_unlock(d);

		rfcomm_send_msc(s, 0, dlci, msc->v24_sig);

		d->mscex |= RFCOMM_MSCEX_RX;
	} else
		d->mscex |= RFCOMM_MSCEX_TX;

	return 0;
}