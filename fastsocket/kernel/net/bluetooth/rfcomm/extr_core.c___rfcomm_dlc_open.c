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
typedef  int u8 ;
struct rfcomm_session {scalar_t__ cfc; scalar_t__ state; int /*<<< orphan*/  mtu; int /*<<< orphan*/  initiator; } ;
struct rfcomm_dlc {scalar_t__ state; int dlci; int priority; int out; scalar_t__ cfc; int /*<<< orphan*/  flags; int /*<<< orphan*/  mtu; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 scalar_t__ BT_CLOSED ; 
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ BT_OPEN ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  RFCOMM_AUTH_PENDING ; 
 scalar_t__ RFCOMM_CFC_UNKNOWN ; 
 int /*<<< orphan*/  RFCOMM_CONN_TIMEOUT ; 
 int /*<<< orphan*/  __addr (int /*<<< orphan*/ ,int) ; 
 int __dlci (int,int) ; 
 int /*<<< orphan*/  batostr (int /*<<< orphan*/ *) ; 
 scalar_t__ rfcomm_check_security (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_clear_state (struct rfcomm_dlc*) ; 
 scalar_t__ rfcomm_dlc_get (struct rfcomm_session*,int) ; 
 int /*<<< orphan*/  rfcomm_dlc_link (struct rfcomm_session*,struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_set_timer (struct rfcomm_dlc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_send_pn (struct rfcomm_session*,int,struct rfcomm_dlc*) ; 
 struct rfcomm_session* rfcomm_session_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 struct rfcomm_session* rfcomm_session_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __rfcomm_dlc_open(struct rfcomm_dlc *d, bdaddr_t *src, bdaddr_t *dst, u8 channel)
{
	struct rfcomm_session *s;
	int err = 0;
	u8 dlci;

	BT_DBG("dlc %p state %ld %s %s channel %d",
			d, d->state, batostr(src), batostr(dst), channel);

	if (channel < 1 || channel > 30)
		return -EINVAL;

	if (d->state != BT_OPEN && d->state != BT_CLOSED)
		return 0;

	s = rfcomm_session_get(src, dst);
	if (!s) {
		s = rfcomm_session_create(src, dst, &err);
		if (!s)
			return err;
	}

	dlci = __dlci(!s->initiator, channel);

	/* Check if DLCI already exists */
	if (rfcomm_dlc_get(s, dlci))
		return -EBUSY;

	rfcomm_dlc_clear_state(d);

	d->dlci     = dlci;
	d->addr     = __addr(s->initiator, dlci);
	d->priority = 7;

	d->state = BT_CONFIG;
	rfcomm_dlc_link(s, d);

	d->out = 1;

	d->mtu = s->mtu;
	d->cfc = (s->cfc == RFCOMM_CFC_UNKNOWN) ? 0 : s->cfc;

	if (s->state == BT_CONNECTED) {
		if (rfcomm_check_security(d))
			rfcomm_send_pn(s, 1, d);
		else
			set_bit(RFCOMM_AUTH_PENDING, &d->flags);
	}

	rfcomm_dlc_set_timer(d, RFCOMM_CONN_TIMEOUT);

	return 0;
}