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
typedef  unsigned long u8 ;

/* Variables and functions */
 unsigned long SENSORS_LIMIT (unsigned long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u8 IN_TO_REG(unsigned long val)
{
	unsigned long nval = SENSORS_LIMIT(val, 0, 4080);
	return (nval + 8) / 16;
}