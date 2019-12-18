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
typedef  int /*<<< orphan*/  u_short ;

/* Variables and functions */
 int /*<<< orphan*/  debug (int,char*,unsigned int,unsigned int) ; 
 unsigned int inw (unsigned int) ; 

__attribute__((used)) static unsigned int pcc_get(u_short sock, unsigned int reg)
{
	unsigned int val = inw(reg);
	debug(3, "m32r_cfc: pcc_get: reg(0x%08x)=0x%04x\n", reg, val);
	return val;
}