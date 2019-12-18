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
typedef  int u16 ;

/* Variables and functions */
 int HOST_FRAME_MASK ; 

__attribute__((used)) static inline int frame_after_eq(u16 a, u16 b)
{
	return ((HOST_FRAME_MASK + 1 + a - b) & HOST_FRAME_MASK) <
	    (HOST_FRAME_MASK / 2);
}