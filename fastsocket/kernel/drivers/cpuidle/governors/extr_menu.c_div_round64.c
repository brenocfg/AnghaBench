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
typedef  scalar_t__ u64 ;
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ div_u64 (scalar_t__,int) ; 

__attribute__((used)) static u64 div_round64(u64 dividend, u32 divisor)
{
	return div_u64(dividend + (divisor / 2), divisor);
}