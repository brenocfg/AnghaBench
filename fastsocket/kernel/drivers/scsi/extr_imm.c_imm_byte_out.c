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
 int /*<<< orphan*/  w_ctr (unsigned short,int) ; 
 int /*<<< orphan*/  w_dtr (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imm_byte_out(unsigned short base, const char *buffer, int len)
{
	int i;

	w_ctr(base, 0x4);	/* apparently a sane mode */
	for (i = len >> 1; i; i--) {
		w_dtr(base, *buffer++);
		w_ctr(base, 0x5);	/* Drop STROBE low */
		w_dtr(base, *buffer++);
		w_ctr(base, 0x0);	/* STROBE high + INIT low */
	}
	w_ctr(base, 0x4);	/* apparently a sane mode */
	return 1;		/* All went well - we hope! */
}