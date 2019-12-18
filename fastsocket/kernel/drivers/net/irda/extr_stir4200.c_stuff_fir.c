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
typedef  int __u8 ;

/* Variables and functions */
 int IRDA_TRANS ; 

__attribute__((used)) static inline __u8 *stuff_fir(__u8 *p, __u8 c)
{
	switch(c) {
	case 0x7d:
	case 0x7e:
	case 0x7f:
		*p++ = 0x7d;
		c ^= IRDA_TRANS;
		/* fall through */
	default:
		*p++ = c;
	}
	return p;
}