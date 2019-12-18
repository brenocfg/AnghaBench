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
typedef  int s8 ;

/* Variables and functions */
 int SENSORS_LIMIT (int,int,int) ; 

__attribute__((used)) static inline s8 TEMP_TO_REG(int val)
{
	int nval = SENSORS_LIMIT(val, -128000, 127000) ;
	return nval<0 ? (nval-500)/1000 : (nval+500)/1000;
}