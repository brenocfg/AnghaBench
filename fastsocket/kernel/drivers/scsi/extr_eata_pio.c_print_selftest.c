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

/* Variables and functions */
 int /*<<< orphan*/  EATA_CMD_PIO_SETUPTEST ; 
 scalar_t__ HA_RDATA ; 
 scalar_t__ HA_RSTATUS ; 
 int HA_SBUSY ; 
 int HA_SDRQ ; 
 int HA_SERROR ; 
 scalar_t__ HA_WCOMMAND ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  insw (scalar_t__,unsigned char**,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static unsigned int print_selftest(unsigned int base)
{
	unsigned char buffer[512];
#ifdef VERBOSE_SETUP
	int z;
#endif

	printk("eata_pio: executing controller self test & setup...\n");
	while (inb(base + HA_RSTATUS) & HA_SBUSY);
	outb(EATA_CMD_PIO_SETUPTEST, base + HA_WCOMMAND);
	do {
		while (inb(base + HA_RSTATUS) & HA_SBUSY)
			/* nothing */ ;
		if (inb(base + HA_RSTATUS) & HA_SDRQ) {
			insw(base + HA_RDATA, &buffer, 256);
#ifdef VERBOSE_SETUP
			/* no beeps please... */
			for (z = 0; z < 511 && buffer[z]; z++)
				if (buffer[z] != 7)
					printk("%c", buffer[z]);
#endif
		}
	} while (inb(base + HA_RSTATUS) & (HA_SBUSY | HA_SDRQ));

	return (!(inb(base + HA_RSTATUS) & HA_SERROR));
}