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
struct rfcomm_dlc {int /*<<< orphan*/  flags; int /*<<< orphan*/  v24_sig; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFCOMM_MSC_PENDING ; 
 int /*<<< orphan*/  RFCOMM_RX_THROTTLED ; 
 int /*<<< orphan*/  RFCOMM_SCHED_TX ; 
 int /*<<< orphan*/  RFCOMM_V24_FC ; 
 int /*<<< orphan*/  rfcomm_schedule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rfcomm_dlc_set_modem_status(struct rfcomm_dlc *d, u8 v24_sig)
{
	BT_DBG("dlc %p state %ld v24_sig 0x%x",
			d, d->state, v24_sig);

	if (test_bit(RFCOMM_RX_THROTTLED, &d->flags))
		v24_sig |= RFCOMM_V24_FC;
	else
		v24_sig &= ~RFCOMM_V24_FC;

	d->v24_sig = v24_sig;

	if (!test_and_set_bit(RFCOMM_MSC_PENDING, &d->flags))
		rfcomm_schedule(RFCOMM_SCHED_TX);

	return 0;
}