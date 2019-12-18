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
struct snd_opl3sa2 {unsigned char* ctlregs; scalar_t__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 scalar_t__ port ; 

__attribute__((used)) static void __snd_opl3sa2_write(struct snd_opl3sa2 *chip, unsigned char reg, unsigned char value)
{
#if 0
	outb(0x1d, port);	/* password */
#endif
	outb(reg, chip->port);	/* register */
	outb(value, chip->port + 1);
	chip->ctlregs[reg] = value;
}