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
struct TYPE_3__ {int flags; int /*<<< orphan*/  resetString; int /*<<< orphan*/  name; int /*<<< orphan*/  string; int /*<<< orphan*/ * latchedString; struct TYPE_3__* next; } ;
typedef  TYPE_1__ cvar_t ;

/* Variables and functions */
 int CVAR_CHEAT ; 
 int /*<<< orphan*/  Cvar_Set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_Free (int /*<<< orphan*/ *) ; 
 TYPE_1__* cvar_vars ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Cvar_SetCheatState( void ) {
	cvar_t	*var;

	// set all default vars to the safe value
	for ( var = cvar_vars ; var ; var = var->next ) {
		if ( var->flags & CVAR_CHEAT ) {
      // the CVAR_LATCHED|CVAR_CHEAT vars might escape the reset here 
      // because of a different var->latchedString
      if (var->latchedString)
      {
        Z_Free(var->latchedString);
        var->latchedString = NULL;
      }
			if (strcmp(var->resetString,var->string)) {
        Cvar_Set( var->name, var->resetString );
			}
		}
	}
}