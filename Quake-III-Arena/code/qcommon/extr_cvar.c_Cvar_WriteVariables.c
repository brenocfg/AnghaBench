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
typedef  int /*<<< orphan*/  fileHandle_t ;
struct TYPE_3__ {int flags; scalar_t__ string; int /*<<< orphan*/  name; scalar_t__ latchedString; struct TYPE_3__* next; } ;
typedef  TYPE_1__ cvar_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FS_Printf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* cvar_vars ; 

void Cvar_WriteVariables( fileHandle_t f ) {
	cvar_t	*var;
	char	buffer[1024];

	for (var = cvar_vars ; var ; var = var->next) {
		if( Q_stricmp( var->name, "cl_cdkey" ) == 0 ) {
			continue;
		}
		if( var->flags & CVAR_ARCHIVE ) {
			// write the latched value, even if it hasn't taken effect yet
			if ( var->latchedString ) {
				Com_sprintf (buffer, sizeof(buffer), "seta %s \"%s\"\n", var->name, var->latchedString);
			} else {
				Com_sprintf (buffer, sizeof(buffer), "seta %s \"%s\"\n", var->name, var->string);
			}
			FS_Printf (f, "%s", buffer);
		}
	}
}