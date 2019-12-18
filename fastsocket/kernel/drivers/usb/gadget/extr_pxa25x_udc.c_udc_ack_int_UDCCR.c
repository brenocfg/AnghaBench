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
typedef  int __u32 ;

/* Variables and functions */
 int UDCCR ; 
 int UDCCR_MASK_BITS ; 

__attribute__((used)) static inline void udc_ack_int_UDCCR(int mask)
{
	/* udccr contains the bits we dont want to change */
	__u32 udccr = UDCCR & UDCCR_MASK_BITS;

	UDCCR = udccr | (mask & ~UDCCR_MASK_BITS);
}