#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* shader; scalar_t__ fogNum; scalar_t__ dlightBits; int /*<<< orphan*/  indexes; int /*<<< orphan*/  numIndexes; int /*<<< orphan*/  numVertexes; int /*<<< orphan*/ ** texCoords; TYPE_1__** xstages; int /*<<< orphan*/  constantColor255; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_3__ shaderCommands_t ;
struct TYPE_11__ {scalar_t__ integer; } ;
struct TYPE_10__ {scalar_t__ integer; } ;
struct TYPE_8__ {scalar_t__ sort; scalar_t__ fogPass; int /*<<< orphan*/  cullType; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/ * bundle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLS_DEFAULT ; 
 int /*<<< orphan*/  GL_COLOR_ARRAY ; 
 int /*<<< orphan*/  GL_Cull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FLAT ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_MODULATE ; 
 int /*<<< orphan*/  GL_REPLACE ; 
 int /*<<< orphan*/  GL_SMOOTH ; 
 int /*<<< orphan*/  GL_SelectTexture (int) ; 
 int /*<<< orphan*/  GL_State (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_COORD_ARRAY ; 
 int /*<<< orphan*/  GL_TexEnv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  GLimp_LogComment (char*) ; 
 int /*<<< orphan*/  ProjectDlightTexture () ; 
 int /*<<< orphan*/  RB_FogPass () ; 
 int /*<<< orphan*/  R_BindAnimatedImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  R_DrawElements (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SS_OPAQUE ; 
 int /*<<< orphan*/  qglColor3f (int,int,int) ; 
 int /*<<< orphan*/  qglColorPointer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDisableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglLockArraysEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglShadeModel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglTexCoordPointer (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglUnlockArraysEXT () ; 
 int /*<<< orphan*/  qglVertexPointer (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_6__* r_lightmap ; 
 TYPE_5__* r_logFile ; 
 TYPE_3__ tess ; 
 char* va (char*,int /*<<< orphan*/ ) ; 

void RB_StageIteratorLightmappedMultitexture( void ) {
	shaderCommands_t *input;

	input = &tess;

	//
	// log this call
	//
	if ( r_logFile->integer ) {
		// don't just call LogComment, or we will get
		// a call to va() every frame!
		GLimp_LogComment( va("--- RB_StageIteratorLightmappedMultitexture( %s ) ---\n", tess.shader->name) );
	}

	//
	// set face culling appropriately
	//
	GL_Cull( input->shader->cullType );

	//
	// set color, pointers, and lock
	//
	GL_State( GLS_DEFAULT );
	qglVertexPointer( 3, GL_FLOAT, 16, input->xyz );

#ifdef REPLACE_MODE
	qglDisableClientState( GL_COLOR_ARRAY );
	qglColor3f( 1, 1, 1 );
	qglShadeModel( GL_FLAT );
#else
	qglEnableClientState( GL_COLOR_ARRAY );
	qglColorPointer( 4, GL_UNSIGNED_BYTE, 0, tess.constantColor255 );
#endif

	//
	// select base stage
	//
	GL_SelectTexture( 0 );

	qglEnableClientState( GL_TEXTURE_COORD_ARRAY );
	R_BindAnimatedImage( &tess.xstages[0]->bundle[0] );
	qglTexCoordPointer( 2, GL_FLOAT, 16, tess.texCoords[0][0] );

	//
	// configure second stage
	//
	GL_SelectTexture( 1 );
	qglEnable( GL_TEXTURE_2D );
	if ( r_lightmap->integer ) {
		GL_TexEnv( GL_REPLACE );
	} else {
		GL_TexEnv( GL_MODULATE );
	}
	R_BindAnimatedImage( &tess.xstages[0]->bundle[1] );
	qglEnableClientState( GL_TEXTURE_COORD_ARRAY );
	qglTexCoordPointer( 2, GL_FLOAT, 16, tess.texCoords[0][1] );

	//
	// lock arrays
	//
	if ( qglLockArraysEXT ) {
		qglLockArraysEXT(0, input->numVertexes);
		GLimp_LogComment( "glLockArraysEXT\n" );
	}

	R_DrawElements( input->numIndexes, input->indexes );

	//
	// disable texturing on TEXTURE1, then select TEXTURE0
	//
	qglDisable( GL_TEXTURE_2D );
	qglDisableClientState( GL_TEXTURE_COORD_ARRAY );

	GL_SelectTexture( 0 );
#ifdef REPLACE_MODE
	GL_TexEnv( GL_MODULATE );
	qglShadeModel( GL_SMOOTH );
#endif

	// 
	// now do any dynamic lighting needed
	//
	if ( tess.dlightBits && tess.shader->sort <= SS_OPAQUE ) {
		ProjectDlightTexture();
	}

	//
	// now do fog
	//
	if ( tess.fogNum && tess.shader->fogPass ) {
		RB_FogPass();
	}

	//
	// unlock arrays
	//
	if ( qglUnlockArraysEXT ) {
		qglUnlockArraysEXT();
		GLimp_LogComment( "glUnlockArraysEXT\n" );
	}
}