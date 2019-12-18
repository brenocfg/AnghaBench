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
struct stmp3xxx_pinmux_bank {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int NR_BANKS ; 
 unsigned int STMP3XXX_PINID_TO_BANK (unsigned int) ; 
 unsigned int STMP3XXX_PINID_TO_PINNUM (unsigned int) ; 
 struct stmp3xxx_pinmux_bank* pinmux_banks ; 

__attribute__((used)) static inline struct stmp3xxx_pinmux_bank *
stmp3xxx_pinmux_bank(unsigned id, unsigned *bank, unsigned *pin)
{
	unsigned b, p;

	b = STMP3XXX_PINID_TO_BANK(id);
	p = STMP3XXX_PINID_TO_PINNUM(id);
	BUG_ON(b >= NR_BANKS);
	if (bank)
		*bank = b;
	if (pin)
		*pin = p;
	return &pinmux_banks[b];
}