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
typedef  int /*<<< orphan*/  skinName ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {int /*<<< orphan*/  animations; void* headModel; void* torsoModel; void* legsModel; } ;
typedef  TYPE_1__ playerInfo_t ;
typedef  int /*<<< orphan*/  modelName ;
typedef  int /*<<< orphan*/  headModelName ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,char*,...) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char*,...) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char const*,int) ; 
 int /*<<< orphan*/  UI_ParseAnimationFile (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_RegisterClientSkin (TYPE_1__*,char*,char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 char* strchr (char*,char) ; 
 void* trap_R_RegisterModel (char*) ; 

qboolean UI_RegisterClientModelname( playerInfo_t *pi, const char *modelSkinName, const char *headModelSkinName, const char *teamName ) {
	char		modelName[MAX_QPATH];
	char		skinName[MAX_QPATH];
	char		headModelName[MAX_QPATH];
	char		headSkinName[MAX_QPATH];
	char		filename[MAX_QPATH];
	char		*slash;

	pi->torsoModel = 0;
	pi->headModel = 0;

	if ( !modelSkinName[0] ) {
		return qfalse;
	}

	Q_strncpyz( modelName, modelSkinName, sizeof( modelName ) );

	slash = strchr( modelName, '/' );
	if ( !slash ) {
		// modelName did not include a skin name
		Q_strncpyz( skinName, "default", sizeof( skinName ) );
	} else {
		Q_strncpyz( skinName, slash + 1, sizeof( skinName ) );
		*slash = '\0';
	}

	Q_strncpyz( headModelName, headModelSkinName, sizeof( headModelName ) );
	slash = strchr( headModelName, '/' );
	if ( !slash ) {
		// modelName did not include a skin name
		Q_strncpyz( headSkinName, "default", sizeof( skinName ) );
	} else {
		Q_strncpyz( headSkinName, slash + 1, sizeof( skinName ) );
		*slash = '\0';
	}

	// load cmodels before models so filecache works

	Com_sprintf( filename, sizeof( filename ), "models/players/%s/lower.md3", modelName );
	pi->legsModel = trap_R_RegisterModel( filename );
	if ( !pi->legsModel ) {
		Com_sprintf( filename, sizeof( filename ), "models/players/characters/%s/lower.md3", modelName );
		pi->legsModel = trap_R_RegisterModel( filename );
		if ( !pi->legsModel ) {
			Com_Printf( "Failed to load model file %s\n", filename );
			return qfalse;
		}
	}

	Com_sprintf( filename, sizeof( filename ), "models/players/%s/upper.md3", modelName );
	pi->torsoModel = trap_R_RegisterModel( filename );
	if ( !pi->torsoModel ) {
		Com_sprintf( filename, sizeof( filename ), "models/players/characters/%s/upper.md3", modelName );
		pi->torsoModel = trap_R_RegisterModel( filename );
		if ( !pi->torsoModel ) {
			Com_Printf( "Failed to load model file %s\n", filename );
			return qfalse;
		}
	}

	if (headModelName && headModelName[0] == '*' ) {
		Com_sprintf( filename, sizeof( filename ), "models/players/heads/%s/%s.md3", &headModelName[1], &headModelName[1] );
	}
	else {
		Com_sprintf( filename, sizeof( filename ), "models/players/%s/head.md3", headModelName );
	}
	pi->headModel = trap_R_RegisterModel( filename );
	if ( !pi->headModel && headModelName[0] != '*') {
		Com_sprintf( filename, sizeof( filename ), "models/players/heads/%s/%s.md3", headModelName, headModelName );
		pi->headModel = trap_R_RegisterModel( filename );
	}

	if (!pi->headModel) {
		Com_Printf( "Failed to load model file %s\n", filename );
		return qfalse;
	}

	// if any skins failed to load, fall back to default
	if ( !UI_RegisterClientSkin( pi, modelName, skinName, headModelName, headSkinName, teamName) ) {
		if ( !UI_RegisterClientSkin( pi, modelName, "default", headModelName, "default", teamName ) ) {
			Com_Printf( "Failed to load skin file: %s : %s\n", modelName, skinName );
			return qfalse;
		}
	}

	// load the animations
	Com_sprintf( filename, sizeof( filename ), "models/players/%s/animation.cfg", modelName );
	if ( !UI_ParseAnimationFile( filename, pi->animations ) ) {
		Com_sprintf( filename, sizeof( filename ), "models/players/characters/%s/animation.cfg", modelName );
		if ( !UI_ParseAnimationFile( filename, pi->animations ) ) {
			Com_Printf( "Failed to load animation file %s\n", filename );
			return qfalse;
		}
	}

	return qtrue;
}