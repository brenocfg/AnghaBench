#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct el3_private {scalar_t__ type; } ;
typedef  int __be16 ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ EL3_PNP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int current_tag ; 
 int el3_cards ; 
 int el3_debug ; 
 TYPE_1__** el3_devs ; 
 int htons (int) ; 
 int /*<<< orphan*/  id_port ; 
 int id_read_eeprom (int) ; 
 int /*<<< orphan*/  memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct el3_private* netdev_priv (TYPE_1__*) ; 
 int /*<<< orphan*/  nopnp ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int,int,int) ; 

__attribute__((used)) static int el3_isa_id_sequence(__be16 *phys_addr)
{
	short lrs_state = 0xff;
	int i;

	/* ISA boards are detected by sending the ID sequence to the
	   ID_PORT.  We find cards past the first by setting the 'current_tag'
	   on cards as they are found.  Cards with their tag set will not
	   respond to subsequent ID sequences. */

	outb(0x00, id_port);
	outb(0x00, id_port);
	for (i = 0; i < 255; i++) {
		outb(lrs_state, id_port);
		lrs_state <<= 1;
		lrs_state = lrs_state & 0x100 ? lrs_state ^ 0xcf : lrs_state;
	}
	/* For the first probe, clear all board's tag registers. */
	if (current_tag == 0)
		outb(0xd0, id_port);
	else			/* Otherwise kill off already-found boards. */
		outb(0xd8, id_port);
	if (id_read_eeprom(7) != 0x6d50)
		return 1;
	/* Read in EEPROM data, which does contention-select.
	   Only the lowest address board will stay "on-line".
	   3Com got the byte order backwards. */
	for (i = 0; i < 3; i++)
		phys_addr[i] = htons(id_read_eeprom(i));
#ifdef CONFIG_PNP
	if (!nopnp) {
		/* The ISA PnP 3c509 cards respond to the ID sequence too.
		   This check is needed in order not to register them twice. */
		for (i = 0; i < el3_cards; i++) {
			struct el3_private *lp = netdev_priv(el3_devs[i]);
			if (lp->type == EL3_PNP
			    && !memcmp(phys_addr, el3_devs[i]->dev_addr,
				       ETH_ALEN)) {
				if (el3_debug > 3)
					pr_debug("3c509 with address %02x %02x %02x %02x %02x %02x was found by ISAPnP\n",
						phys_addr[0] & 0xff, phys_addr[0] >> 8,
						phys_addr[1] & 0xff, phys_addr[1] >> 8,
						phys_addr[2] & 0xff, phys_addr[2] >> 8);
				/* Set the adaptor tag so that the next card can be found. */
				outb(0xd0 + ++current_tag, id_port);
				return 2;
			}
		}
	}
#endif /* CONFIG_PNP */
	return 0;

}