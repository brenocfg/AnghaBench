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
typedef  scalar_t__ int16 ;

/* Variables and functions */
 int DB2LIN_AMP_BITS ; 
 scalar_t__* DB2LIN_TABLE ; 
 size_t DB_MUTE ; 
 double DB_STEP ; 
 double pow (int,double) ; 

__attribute__((used)) static void makeDB2LinTable(void) {
	int32 i;

	for (i = 0; i < DB_MUTE + DB_MUTE; i++) {
		DB2LIN_TABLE[i] = (int16)((double)((1 << DB2LIN_AMP_BITS) - 1) * pow(10, -(double)i * DB_STEP / 20));
		if (i >= DB_MUTE) DB2LIN_TABLE[i] = 0;
		DB2LIN_TABLE[i + DB_MUTE + DB_MUTE] = (int16)(-DB2LIN_TABLE[i]);
	}
}