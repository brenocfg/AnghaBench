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
typedef  int /*<<< orphan*/  md3Header_t ;
struct TYPE_3__ {int /*<<< orphan*/ * header; int /*<<< orphan*/  modelName; } ;
typedef  TYPE_1__ loadedModel_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_LOADED_MODELS ; 
 int /*<<< orphan*/ * R_LoadMD3 (char const*) ; 
 TYPE_1__* loadedModels ; 
 int numLoadedModels ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

md3Header_t *LoadModel( const char *modelName ) {
	int				i;
	loadedModel_t	*lm;

	// see if we already have it loaded
	for ( i = 0, lm = loadedModels ; i < numLoadedModels ; i++, lm++ ) {
		if ( !strcmp( modelName, lm->modelName ) ) {
			return lm->header;
		}
	}

	// load it
	if ( numLoadedModels == MAX_LOADED_MODELS ) {
		Error( "MAX_LOADED_MODELS" );
	}
	numLoadedModels++;

	strcpy( lm->modelName, modelName );

	lm->header = R_LoadMD3( modelName );

	return lm->header;
}