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
 double PI ; 
 scalar_t__ PM_AMP ; 
 scalar_t__ PM_DEPTH ; 
 size_t PM_PG_WIDTH ; 
 size_t* pmtable ; 
 double pow (int,double) ; 
 double sin (double) ; 

__attribute__((used)) static void makePmTable(void) {
	int32 i;

	for (i = 0; i < PM_PG_WIDTH; i++)
		pmtable[i] = (int32)((double)PM_AMP * pow(2, (double)PM_DEPTH * sin(2.0 * PI * i / PM_PG_WIDTH) / 1200));
}