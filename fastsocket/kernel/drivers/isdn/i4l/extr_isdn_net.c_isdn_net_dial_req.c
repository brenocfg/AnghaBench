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
typedef  int /*<<< orphan*/  isdn_net_local ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ ISDN_NET_DIALMODE (int /*<<< orphan*/ ) ; 
 scalar_t__ ISDN_NET_DM_AUTO ; 
 int isdn_net_force_dial_lp (int /*<<< orphan*/ *) ; 

int
isdn_net_dial_req(isdn_net_local * lp)
{
	/* is there a better error code? */
	if (!(ISDN_NET_DIALMODE(*lp) == ISDN_NET_DM_AUTO)) return -EBUSY;

	return isdn_net_force_dial_lp(lp);
}