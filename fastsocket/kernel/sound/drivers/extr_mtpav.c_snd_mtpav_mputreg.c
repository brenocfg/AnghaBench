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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct mtpav {scalar_t__ port; } ;

/* Variables and functions */
 scalar_t__ CREG ; 
 scalar_t__ DREG ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void snd_mtpav_mputreg(struct mtpav *chip, u16 reg, u8 val)
{
	if (reg == DREG || reg == CREG)
		outb(val, chip->port + reg);
}