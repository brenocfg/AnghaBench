#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  devicename; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENODEV ; 
 int /*<<< orphan*/  ISDN_STAT_BCONN ; 
 int /*<<< orphan*/  IS_VALID_CARD (int) ; 
 int /*<<< orphan*/  hangup (int,unsigned long) ; 
 int /*<<< orphan*/  indicate_status (int,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 TYPE_1__** sc_adapter ; 
 scalar_t__ setup_buffers (int,unsigned long) ; 

__attribute__((used)) static int acceptb(int card, unsigned long channel)
{
	if(!IS_VALID_CARD(card)) {
		pr_debug("Invalid param: %d is not a valid card id\n", card);
		return -ENODEV;
	}

	if(setup_buffers(card, channel+1))
	{
		hangup(card, channel+1);
		return -ENOBUFS;
	}

	pr_debug("%s: B-Channel connection accepted on channel %lu\n",
		sc_adapter[card]->devicename, channel+1);
	indicate_status(card, ISDN_STAT_BCONN, channel, NULL);
	return 0;
}