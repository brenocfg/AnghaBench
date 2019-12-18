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
struct rfcomm_dlc {int v24_sig; int /*<<< orphan*/  rx_credits; int /*<<< orphan*/  cfc; int /*<<< orphan*/  mtu; scalar_t__ mscex; scalar_t__ flags; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  BT_OPEN ; 
 int /*<<< orphan*/  RFCOMM_CFC_DISABLED ; 
 int /*<<< orphan*/  RFCOMM_DEFAULT_CREDITS ; 
 int /*<<< orphan*/  RFCOMM_DEFAULT_MTU ; 
 int RFCOMM_V24_DV ; 
 int RFCOMM_V24_RTC ; 
 int RFCOMM_V24_RTR ; 

__attribute__((used)) static void rfcomm_dlc_clear_state(struct rfcomm_dlc *d)
{
	BT_DBG("%p", d);

	d->state      = BT_OPEN;
	d->flags      = 0;
	d->mscex      = 0;
	d->mtu        = RFCOMM_DEFAULT_MTU;
	d->v24_sig    = RFCOMM_V24_RTC | RFCOMM_V24_RTR | RFCOMM_V24_DV;

	d->cfc        = RFCOMM_CFC_DISABLED;
	d->rx_credits = RFCOMM_DEFAULT_CREDITS;
}