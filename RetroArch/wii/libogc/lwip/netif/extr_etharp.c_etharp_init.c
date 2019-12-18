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
typedef  size_t u8_t ;
struct TYPE_2__ {scalar_t__ ctime; int /*<<< orphan*/ * p; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 size_t ARP_TABLE_SIZE ; 
 int /*<<< orphan*/  ETHARP_STATE_EMPTY ; 
 TYPE_1__* arp_table ; 

void
etharp_init(void)
{
  u8_t i;
  /* clear ARP entries */
  for(i = 0; i < ARP_TABLE_SIZE; ++i) {
    arp_table[i].state = ETHARP_STATE_EMPTY;
#if ARP_QUEUEING
    arp_table[i].p = NULL;
#endif
    arp_table[i].ctime = 0;
  }
}