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
typedef  int /*<<< orphan*/  val ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  read_frandom (int*,int) ; 

uint32_t my_random(void)
{
	uint32_t val;
	read_frandom(&val, sizeof(val));
	val &= 0x7FFFFFFF;

	return (val);
}