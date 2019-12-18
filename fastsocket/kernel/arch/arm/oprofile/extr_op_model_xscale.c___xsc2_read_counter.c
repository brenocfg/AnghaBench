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
#define  CCNT 132 
#define  PMN0 131 
#define  PMN1 130 
#define  PMN2 129 
#define  PMN3 128 

__attribute__((used)) static u32 __xsc2_read_counter(int counter)
{
	u32 val = 0;

	switch (counter) {
	case CCNT:
		__asm__ __volatile__ ("mrc p14, 0, %0, c1, c1, 0" : "=r" (val));
		break;
	case PMN0:
		__asm__ __volatile__ ("mrc p14, 0, %0, c0, c2, 0" : "=r" (val));
		break;
	case PMN1:
		__asm__ __volatile__ ("mrc p14, 0, %0, c1, c2, 0" : "=r" (val));
		break;
	case PMN2:
		__asm__ __volatile__ ("mrc p14, 0, %0, c2, c2, 0" : "=r" (val));
		break;
	case PMN3:
		__asm__ __volatile__ ("mrc p14, 0, %0, c3, c2, 0" : "=r" (val));
		break;
	}
	return val;
}