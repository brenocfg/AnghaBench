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
typedef  unsigned long long u64 ;
struct TYPE_2__ {unsigned long long upper_shift; unsigned long long upper_mask; int /*<<< orphan*/  lower_mask; } ;
struct rsxx_cardinfo {TYPE_1__ _stripe; } ;
typedef  unsigned long long addr8 ;

/* Variables and functions */
 int /*<<< orphan*/  RSXX_HW_BLK_SIZE ; 
 int /*<<< orphan*/  do_div (unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int rsxx_addr8_to_laddr(u64 addr8, struct rsxx_cardinfo *card)
{
	unsigned long long tgt_addr8;

	tgt_addr8 = ((addr8 >> card->_stripe.upper_shift) &
		      card->_stripe.upper_mask) |
		    ((addr8) & card->_stripe.lower_mask);
	do_div(tgt_addr8, RSXX_HW_BLK_SIZE);
	return tgt_addr8;
}