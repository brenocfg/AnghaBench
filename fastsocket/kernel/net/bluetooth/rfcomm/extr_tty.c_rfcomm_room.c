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
struct rfcomm_dlc {int mtu; scalar_t__ tx_credits; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int rfcomm_room(struct rfcomm_dlc *dlc)
{
	/* We can't let it be zero, because we don't get a callback
	   when tx_credits becomes nonzero, hence we'd never wake up */
	return dlc->mtu * (dlc->tx_credits?:1);
}