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
#define  FE_TONEAREST 128 
 int fegetround () ; 

int __flt_rounds()
{
	switch (fegetround()) {
#ifdef FE_TOWARDZERO
	case FE_TOWARDZERO: return 0;
#endif
	case FE_TONEAREST: return 1;
#ifdef FE_UPWARD
	case FE_UPWARD: return 2;
#endif
#ifdef FE_DOWNWARD
	case FE_DOWNWARD: return 3;
#endif
	}
	return -1;
}