#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* buffer; scalar_t__ cursor; } ;
typedef  TYPE_1__ field_t ;

/* Variables and functions */
 int Cmd_Argc () ; 
 char* Cmd_Argv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cmd_CommandCompletion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cmd_TokenizeString (char*) ; 
 int /*<<< orphan*/  Com_Memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,scalar_t__*) ; 
 int /*<<< orphan*/  ConcatRemaining (char*,char*) ; 
 int /*<<< orphan*/  Cvar_CommandCompletion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindMatches ; 
 int /*<<< orphan*/  PrintMatches ; 
 int /*<<< orphan*/  Q_strcat (char*,int,char*) ; 
 TYPE_1__* completionField ; 
 char* completionString ; 
 int matchCount ; 
 scalar_t__* shortestMatch ; 
 scalar_t__ strlen (char*) ; 

void Field_CompleteCommand( field_t *field ) {
	field_t		temp;

	completionField = field;

	// only look at the first token for completion purposes
	Cmd_TokenizeString( completionField->buffer );

	completionString = Cmd_Argv(0);
	if ( completionString[0] == '\\' || completionString[0] == '/' ) {
		completionString++;
	}
	matchCount = 0;
	shortestMatch[0] = 0;

	if ( strlen( completionString ) == 0 ) {
		return;
	}

	Cmd_CommandCompletion( FindMatches );
	Cvar_CommandCompletion( FindMatches );

	if ( matchCount == 0 ) {
		return;	// no matches
	}

	Com_Memcpy(&temp, completionField, sizeof(field_t));

	if ( matchCount == 1 ) {
		Com_sprintf( completionField->buffer, sizeof( completionField->buffer ), "\\%s", shortestMatch );
		if ( Cmd_Argc() == 1 ) {
			Q_strcat( completionField->buffer, sizeof( completionField->buffer ), " " );
		} else {
			ConcatRemaining( temp.buffer, completionString );
		}
		completionField->cursor = strlen( completionField->buffer );
		return;
	}

	// multiple matches, complete to shortest
	Com_sprintf( completionField->buffer, sizeof( completionField->buffer ), "\\%s", shortestMatch );
	completionField->cursor = strlen( completionField->buffer );
	ConcatRemaining( temp.buffer, completionString );

	Com_Printf( "]%s\n", completionField->buffer );

	// run through again, printing matches
	Cmd_CommandCompletion( PrintMatches );
	Cvar_CommandCompletion( PrintMatches );
}