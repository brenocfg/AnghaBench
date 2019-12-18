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
typedef  size_t int32 ;

/* Variables and functions */
 scalar_t__ AM_DEPTH ; 
 size_t AM_PG_WIDTH ; 
 double DB_STEP ; 
 double PI ; 
 double PM_PG_WIDTH ; 
 size_t* amtable ; 
 double sin (double) ; 

__attribute__((used)) static void makeAmTable(void) {
	int32 i;

	for (i = 0; i < AM_PG_WIDTH; i++)
		amtable[i] = (int32)((double)AM_DEPTH / 2 / DB_STEP * (1.0 + sin(2.0 * PI * i / PM_PG_WIDTH)));
}