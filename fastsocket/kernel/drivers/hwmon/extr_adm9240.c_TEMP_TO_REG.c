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
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  SCALE (long,int,int) ; 
 int /*<<< orphan*/  SENSORS_LIMIT (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline s8 TEMP_TO_REG(long val)
{
	return SENSORS_LIMIT(SCALE(val, 1, 1000), -40, 127);
}