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
typedef  unsigned long u_char ;

/* Variables and functions */
 int /*<<< orphan*/  OUTB_P (int,unsigned short) ; 

__attribute__((used)) static inline void
icn_shiftout(unsigned short port,
	     unsigned long val,
	     int firstbit,
	     int bitcount)
{

	register u_char s;
	register u_char c;

	for (s = firstbit, c = bitcount; c > 0; s--, c--)
		OUTB_P((u_char) ((val >> s) & 1) ? 0xff : 0, port);
}