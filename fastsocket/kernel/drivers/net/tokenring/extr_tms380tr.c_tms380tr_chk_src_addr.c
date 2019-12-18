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
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static void tms380tr_chk_src_addr(unsigned char *frame, unsigned char *hw_addr)
{
	unsigned char SRBit;

	if((((unsigned long)frame[8]) & ~0x80) != 0)	/* Compare 4 bytes */
		return;
	if((unsigned short)frame[12] != 0)		/* Compare 2 bytes */
		return;

	SRBit = frame[8] & 0x80;
	memcpy(&frame[8], hw_addr, 6);
	frame[8] |= SRBit;

	return;
}