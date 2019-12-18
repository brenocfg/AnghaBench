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
struct snd_wss {unsigned char* cimage; scalar_t__ cport; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void snd_cs4236_ctrl_out(struct snd_wss *chip,
				unsigned char reg, unsigned char val)
{
	outb(reg, chip->cport + 3);
	outb(chip->cimage[reg] = val, chip->cport + 4);
}