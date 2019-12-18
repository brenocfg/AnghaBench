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
typedef  int UINT32 ;
typedef  int UINT16 ;

/* Variables and functions */
 int DASMFLAG_STEP_OVER ; 
 int DASMFLAG_STEP_OVER_EXTRA (int) ; 
 int SIGNX12 (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static UINT32 op1011(char *buffer, UINT32 pc, UINT16 opcode)
{
	sprintf(buffer, "BSR     $%08x", SIGNX12(opcode & 0xfff) * 2 + pc + 2);
	return DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);
}