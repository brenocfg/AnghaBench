#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  BasePC; } ;
typedef  TYPE_1__ cz80_struc ;
typedef  scalar_t__ FPTR ;

/* Variables and functions */
 int /*<<< orphan*/  CZ80_PC ; 
 int /*<<< orphan*/  Cz80_Set_Reg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

void Cz80_Reset(cz80_struc *CPU)
{
	memset(CPU, 0, (FPTR)&CPU->BasePC - (FPTR)CPU);
	Cz80_Set_Reg(CPU, CZ80_PC, 0);
}