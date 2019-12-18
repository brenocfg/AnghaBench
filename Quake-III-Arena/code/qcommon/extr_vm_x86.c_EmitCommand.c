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
typedef  int ELastCommand ;

/* Variables and functions */
 int /*<<< orphan*/  EmitString (char*) ; 
#define  LAST_COMMAND_MOV_EDI_EAX 130 
#define  LAST_COMMAND_SUB_DI_4 129 
#define  LAST_COMMAND_SUB_DI_8 128 
 int LastCommand ; 

__attribute__((used)) static void EmitCommand(ELastCommand command)
{
	switch(command)
	{
		case LAST_COMMAND_MOV_EDI_EAX:
			EmitString( "89 07" );		// mov dword ptr [edi], eax
			break;

		case LAST_COMMAND_SUB_DI_4:
			EmitString( "83 EF 04" );	// sub edi, 4
			break;

		case LAST_COMMAND_SUB_DI_8:
			EmitString( "83 EF 08" );	// sub edi, 8
			break;
		default:
			break;
	}
	LastCommand = command;
}