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
struct TYPE_2__ {int /*<<< orphan*/  reg_timerctrl; int /*<<< orphan*/  reg_timerdata; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;

/* Variables and functions */
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __snd_gf1_adlib_write(struct snd_gus_card * gus,
					 unsigned char reg, unsigned char data)
{
	outb(reg, gus->gf1.reg_timerctrl);
	inb(gus->gf1.reg_timerctrl);
	inb(gus->gf1.reg_timerctrl);
	outb(data, gus->gf1.reg_timerdata);
	inb(gus->gf1.reg_timerctrl);
	inb(gus->gf1.reg_timerctrl);
}