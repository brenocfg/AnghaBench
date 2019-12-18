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
struct sport_device {int tx_frags; int rx_frags; } ;

/* Variables and functions */

void sport_decfrag(struct sport_device *sport, int *frag, int tx)
{
	--(*frag);
	if (tx == 1 && *frag == 0)
		*frag = sport->tx_frags;

	if (tx == 0 && *frag == 0)
		*frag = sport->rx_frags;
}