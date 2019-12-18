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
typedef  int __wsum ;

/* Variables and functions */

__attribute__((used)) static inline unsigned short from32to16(__wsum sum)
{
	asm("	add	%1,%0		\n"
	    "	addc	0xffff,%0	\n"
	    : "=r" (sum)
	    : "r" (sum << 16), "0" (sum & 0xffff0000)
	    );
	return sum >> 16;
}