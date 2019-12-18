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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  CCNT 130 
#define  PMN0 129 
#define  PMN1 128 

__attribute__((used)) static void __xsc1_write_counter(int counter, u32 val)
{
	switch (counter) {
	case CCNT:
		__asm__ __volatile__ ("mcr p14, 0, %0, c1, c0, 0" : : "r" (val));
		break;
	case PMN0:
		__asm__ __volatile__ ("mcr p14, 0, %0, c2, c0, 0" : : "r" (val));
		break;
	case PMN1:
		__asm__ __volatile__ ("mcr p14, 0, %0, c3, c0, 0" : : "r" (val));
		break;
	}
}