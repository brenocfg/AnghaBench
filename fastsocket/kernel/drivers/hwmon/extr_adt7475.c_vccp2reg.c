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
typedef  long u16 ;

/* Variables and functions */
 long SENSORS_LIMIT (long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u16 vccp2reg(long vcc)
{
	vcc = SENSORS_LIMIT(vcc, 0, 2998);
	return (vcc * 1000) / 2929;
}