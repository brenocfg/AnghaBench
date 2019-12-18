#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* channel; } ;
struct TYPE_3__ {int l3_proto; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IS_VALID_CARD (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 TYPE_2__** sc_adapter ; 

__attribute__((used)) static int setl3(int card, unsigned long channel)
{
	int protocol = channel >> 8;

	if(!IS_VALID_CARD(card)) {
		pr_debug("Invalid param: %d is not a valid card id\n", card);
		return -ENODEV;
	}

	sc_adapter[card]->channel[channel].l3_proto = protocol;
	return 0;
}