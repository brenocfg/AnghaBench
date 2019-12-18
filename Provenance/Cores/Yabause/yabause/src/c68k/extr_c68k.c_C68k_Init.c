#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  Status; int /*<<< orphan*/  Reset_CallBack; int /*<<< orphan*/ * Interrupt_CallBack; } ;
typedef  TYPE_1__ c68k_struc ;
typedef  int /*<<< orphan*/  C68K_INT_CALLBACK ;

/* Variables and functions */
 int /*<<< orphan*/  C68K_DISABLE ; 
 int /*<<< orphan*/  C68k_Exec (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * C68k_Interrupt_Ack_Dummy ; 
 int /*<<< orphan*/  C68k_Read_Dummy ; 
 int /*<<< orphan*/  C68k_Reset_Dummy ; 
 int /*<<< orphan*/  C68k_Set_ReadB (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  C68k_Set_ReadW (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  C68k_Set_WriteB (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  C68k_Set_WriteW (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  C68k_Write_Dummy ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void C68k_Init(c68k_struc *cpu, C68K_INT_CALLBACK *int_cb)
{
    memset(cpu, 0, sizeof(c68k_struc));

    C68k_Set_ReadB(cpu, C68k_Read_Dummy);
    C68k_Set_ReadW(cpu, C68k_Read_Dummy);

    C68k_Set_WriteB(cpu, C68k_Write_Dummy);
    C68k_Set_WriteW(cpu, C68k_Write_Dummy);

    if (int_cb) cpu->Interrupt_CallBack = int_cb;
    else cpu->Interrupt_CallBack = C68k_Interrupt_Ack_Dummy;
    cpu->Reset_CallBack = C68k_Reset_Dummy;

    // used to init JumpTable
    cpu->Status |= C68K_DISABLE;
    C68k_Exec(cpu, 0);
    
    cpu->Status &= ~C68K_DISABLE;
}