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
struct snd_emu10k1 {unsigned long port; } ;

/* Variables and functions */
 unsigned short EC_NUM_CONTROL_BITS ; 
 unsigned int HANDN_BIT ; 
 unsigned long HCFG ; 
 unsigned int HOOKN_BIT ; 
 unsigned int PULSEN_BIT ; 
 unsigned int inl (unsigned long) ; 
 int /*<<< orphan*/  outl (unsigned int,unsigned long) ; 

__attribute__((used)) static void snd_emu10k1_ecard_write(struct snd_emu10k1 *emu, unsigned int value)
{
	unsigned short count;
	unsigned int data;
	unsigned long hc_port;
	unsigned int hc_value;

	hc_port = emu->port + HCFG;
	hc_value = inl(hc_port) & ~(HOOKN_BIT | HANDN_BIT | PULSEN_BIT);
	outl(hc_value, hc_port);

	for (count = 0; count < EC_NUM_CONTROL_BITS; count++) {

		/* Set up the value */
		data = ((value & 0x1) ? PULSEN_BIT : 0);
		value >>= 1;

		outl(hc_value | data, hc_port);

		/* Clock the shift register */
		outl(hc_value | data | HANDN_BIT, hc_port);
		outl(hc_value | data, hc_port);
	}

	/* Latch the bits */
	outl(hc_value | HOOKN_BIT, hc_port);
	outl(hc_value, hc_port);
}