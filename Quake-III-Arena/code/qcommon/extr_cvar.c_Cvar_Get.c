#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; char* resetString; char* latchedString; int modificationCount; struct TYPE_7__* hashNext; struct TYPE_7__* next; void* string; int /*<<< orphan*/  integer; int /*<<< orphan*/  value; int /*<<< orphan*/  modified; void* name; } ;
typedef  TYPE_1__ cvar_t ;

/* Variables and functions */
 int CVAR_ROM ; 
 int CVAR_USER_CREATED ; 
 int /*<<< orphan*/  Com_DPrintf (char*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,char const*) ; 
 void* CopyString (char const*) ; 
 TYPE_1__* Cvar_FindVar (char const*) ; 
 int /*<<< orphan*/  Cvar_Set2 (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_ValidateString (char const*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 size_t MAX_CVARS ; 
 int /*<<< orphan*/  Z_Free (char*) ; 
 int /*<<< orphan*/  atof (void*) ; 
 int /*<<< orphan*/  atoi (void*) ; 
 TYPE_1__* cvar_indexes ; 
 int cvar_modifiedFlags ; 
 size_t cvar_numIndexes ; 
 TYPE_1__* cvar_vars ; 
 long generateHashValue (char const*) ; 
 TYPE_1__** hashTable ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ strcmp (char*,char const*) ; 

cvar_t *Cvar_Get( const char *var_name, const char *var_value, int flags ) {
	cvar_t	*var;
	long	hash;

  if ( !var_name || ! var_value ) {
		Com_Error( ERR_FATAL, "Cvar_Get: NULL parameter" );
  }

	if ( !Cvar_ValidateString( var_name ) ) {
		Com_Printf("invalid cvar name string: %s\n", var_name );
		var_name = "BADNAME";
	}

#if 0		// FIXME: values with backslash happen
	if ( !Cvar_ValidateString( var_value ) ) {
		Com_Printf("invalid cvar value string: %s\n", var_value );
		var_value = "BADVALUE";
	}
#endif

	var = Cvar_FindVar (var_name);
	if ( var ) {
		// if the C code is now specifying a variable that the user already
		// set a value for, take the new value as the reset value
		if ( ( var->flags & CVAR_USER_CREATED ) && !( flags & CVAR_USER_CREATED )
			&& var_value[0] ) {
			var->flags &= ~CVAR_USER_CREATED;
			Z_Free( var->resetString );
			var->resetString = CopyString( var_value );

			// ZOID--needs to be set so that cvars the game sets as 
			// SERVERINFO get sent to clients
			cvar_modifiedFlags |= flags;
		}

		var->flags |= flags;
		// only allow one non-empty reset string without a warning
		if ( !var->resetString[0] ) {
			// we don't have a reset string yet
			Z_Free( var->resetString );
			var->resetString = CopyString( var_value );
		} else if ( var_value[0] && strcmp( var->resetString, var_value ) ) {
			Com_DPrintf( "Warning: cvar \"%s\" given initial values: \"%s\" and \"%s\"\n",
				var_name, var->resetString, var_value );
		}
		// if we have a latched string, take that value now
		if ( var->latchedString ) {
			char *s;

			s = var->latchedString;
			var->latchedString = NULL;	// otherwise cvar_set2 would free it
			Cvar_Set2( var_name, s, qtrue );
			Z_Free( s );
		}

// use a CVAR_SET for rom sets, get won't override
#if 0
		// CVAR_ROM always overrides
		if ( flags & CVAR_ROM ) {
			Cvar_Set2( var_name, var_value, qtrue );
		}
#endif
		return var;
	}

	//
	// allocate a new cvar
	//
	if ( cvar_numIndexes >= MAX_CVARS ) {
		Com_Error( ERR_FATAL, "MAX_CVARS" );
	}
	var = &cvar_indexes[cvar_numIndexes];
	cvar_numIndexes++;
	var->name = CopyString (var_name);
	var->string = CopyString (var_value);
	var->modified = qtrue;
	var->modificationCount = 1;
	var->value = atof (var->string);
	var->integer = atoi(var->string);
	var->resetString = CopyString( var_value );

	// link the variable in
	var->next = cvar_vars;
	cvar_vars = var;

	var->flags = flags;

	hash = generateHashValue(var_name);
	var->hashNext = hashTable[hash];
	hashTable[hash] = var;

	return var;
}