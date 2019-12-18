#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {int* buffer; int* curpos; int len; } ;

/* Variables and functions */
 scalar_t__ CharIsTokenDelimiter (char) ; 
 TYPE_1__ ase ; 
 char* s_token ; 

__attribute__((used)) static int ASE_GetToken( qboolean restOfLine )
{
	int i = 0;

	if ( ase.buffer == 0 )
		return 0;

	if ( ( ase.curpos - ase.buffer ) == ase.len )
		return 0;

	// skip over crap
	while ( ( ( ase.curpos - ase.buffer ) < ase.len ) &&
		    ( *ase.curpos <= 32 ) )
	{
		ase.curpos++;
	}

	while ( ( ase.curpos - ase.buffer ) < ase.len )
	{
		s_token[i] = *ase.curpos;

		ase.curpos++;
		i++;

		if ( ( CharIsTokenDelimiter( s_token[i-1] ) && !restOfLine ) ||
			 ( ( s_token[i-1] == '\n' ) || ( s_token[i-1] == '\r' ) ) )
		{
			s_token[i-1] = 0;
			break;
		}
	}

	s_token[i] = 0;

	return 1;
}