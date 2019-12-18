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
typedef  int uint16 ;
typedef  int int32 ;

/* Variables and functions */
 int* AR_ADJUST_TABLE ; 
 int EG_BITS ; 
 int log (int) ; 

__attribute__((used)) static void makeAdjustTable(void) {
	int32 i;

	AR_ADJUST_TABLE[0] = (1 << EG_BITS);
	for (i = 1; i < 128; i++)
		AR_ADJUST_TABLE[i] = (uint16)((double)(1 << EG_BITS) - 1 - (1 << EG_BITS) * log(i) / log(128));
}