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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  c68k_struc ;

/* Variables and functions */
 int /*<<< orphan*/  SET_SR (int /*<<< orphan*/ ) ; 

void C68k_Set_SR(c68k_struc *cpu, u32 val)
{
    c68k_struc *CPU = cpu;
    SET_SR(val);
}