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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int PIC_UPPER_INDEX ; 
 int /*<<< orphan*/  read_pic (int) ; 

__attribute__((used)) static u32 read_pmc(int idx)
{
	u64 val;

	read_pic(val);
	if (idx == PIC_UPPER_INDEX)
		val >>= 32;

	return val & 0xffffffff;
}