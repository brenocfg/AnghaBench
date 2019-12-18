#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_3__ {size_t* A; } ;
typedef  TYPE_1__ c68k_struc ;

/* Variables and functions */

void C68k_Set_AReg(c68k_struc *cpu, u32 num, u32 val)
{
    cpu->A[num] = val;
}