#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xcommand_t ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/ * function; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ cmd_function_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,char const*) ; 
 int /*<<< orphan*/  CopyString (char const*) ; 
 TYPE_1__* S_Malloc (int) ; 
 TYPE_1__* cmd_functions ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

void	Cmd_AddCommand( const char *cmd_name, xcommand_t function ) {
	cmd_function_t	*cmd;
	
	// fail if the command already exists
	for ( cmd = cmd_functions ; cmd ; cmd=cmd->next ) {
		if ( !strcmp( cmd_name, cmd->name ) ) {
			// allow completion-only commands to be silently doubled
			if ( function != NULL ) {
				Com_Printf ("Cmd_AddCommand: %s already defined\n", cmd_name);
			}
			return;
		}
	}

	// use a small malloc to avoid zone fragmentation
	cmd = S_Malloc (sizeof(cmd_function_t));
	cmd->name = CopyString( cmd_name );
	cmd->function = function;
	cmd->next = cmd_functions;
	cmd_functions = cmd;
}