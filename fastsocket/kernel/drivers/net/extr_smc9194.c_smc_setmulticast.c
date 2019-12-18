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
struct dev_mc_list {int* dmi_addr; struct dev_mc_list* next; } ;
typedef  int /*<<< orphan*/  multicast_table ;

/* Variables and functions */
 scalar_t__ MULTICAST1 ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 int ether_crc_le (int,int*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void smc_setmulticast( int ioaddr, int count, struct dev_mc_list * addrs ) {
	int			i;
	unsigned char		multicast_table[ 8 ];
	struct dev_mc_list	* cur_addr;
	/* table for flipping the order of 3 bits */
	unsigned char invert3[] = { 0, 4, 2, 6, 1, 5, 3, 7 };

	/* start with a table of all zeros: reject all */
	memset( multicast_table, 0, sizeof( multicast_table ) );

	cur_addr = addrs;
	for ( i = 0; i < count ; i ++, cur_addr = cur_addr->next  ) {
		int position;

		/* do we have a pointer here? */
		if ( !cur_addr )
			break;
		/* make sure this is a multicast address - shouldn't this
		   be a given if we have it here ? */
		if ( !( *cur_addr->dmi_addr & 1 ) )
			continue;

		/* only use the low order bits */
		position = ether_crc_le(6, cur_addr->dmi_addr) & 0x3f;

		/* do some messy swapping to put the bit in the right spot */
		multicast_table[invert3[position&7]] |=
					(1<<invert3[(position>>3)&7]);

	}
	/* now, the table can be loaded into the chipset */
	SMC_SELECT_BANK( 3 );

	for ( i = 0; i < 8 ; i++ ) {
		outb( multicast_table[i], ioaddr + MULTICAST1 + i );
	}
}