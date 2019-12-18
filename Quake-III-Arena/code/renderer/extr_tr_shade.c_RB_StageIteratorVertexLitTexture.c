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
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ sort; scalar_t__ fogPass; int /*<<< orphan*/  cullType; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ shader_t ;
struct TYPE_7__ {scalar_t__ colors; } ;
struct TYPE_10__ {TYPE_3__* shader; scalar_t__ fogNum; scalar_t__ dlightBits; int /*<<< orphan*/  indexes; int /*<<< orphan*/  numIndexes; TYPE_2__** xstages; int /*<<< orphan*/  numVertexes; int /*<<< orphan*/  xyz; int /*<<< orphan*/ ** texCoords; TYPE_1__ svars; } ;
typedef  TYPE_4__ shaderCommands_t ;
struct TYPE_11__ {scalar_t__ integer; } ;
struct TYPE_8__ {int /*<<< orphan*/  stateBits; int /*<<< orphan*/ * bundle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_ARRAY ; 
 int /*<<< orphan*/  GL_Cull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_State (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_TEXTURE_COORD_ARRAY ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  GLimp_LogComment (char*) ; 
 int /*<<< orphan*/  ProjectDlightTexture () ; 
 int /*<<< orphan*/  RB_CalcDiffuseColor (unsigned char*) ; 
 int /*<<< orphan*/  RB_FogPass () ; 
 int /*<<< orphan*/  R_BindAnimatedImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  R_DrawElements (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SS_OPAQUE ; 
 int /*<<< orphan*/  qglColorPointer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qglEnableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglLockArraysEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglTexCoordPointer (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglUnlockArraysEXT () ; 
 int /*<<< orphan*/  qglVertexPointer (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_6__* r_logFile ; 
 TYPE_4__ tess ; 
 char* va (char*,int /*<<< orphan*/ ) ; 

void RB_StageIteratorVertexLitTexture( void )
{
	shaderCommands_t *input;
	shader_t		*shader;

	input = &tess;

	shader = input->shader;

	//
	// compute colors
	//
	RB_CalcDiffuseColor( ( unsigned char * ) tess.svars.colors );

	//
	// log this call
	//
	if ( r_logFile->integer ) 
	{
		// don't just call LogComment, or we will get
		// a call to va() every frame!
		GLimp_LogComment( va("--- RB_StageIteratorVertexLitTexturedUnfogged( %s ) ---\n", tess.shader->name) );
	}

	//
	// set face culling appropriately
	//
	GL_Cull( input->shader->cullType );

	//
	// set arrays and lock
	//
	qglEnableClientState( GL_COLOR_ARRAY);
	qglEnableClientState( GL_TEXTURE_COORD_ARRAY);

	qglColorPointer( 4, GL_UNSIGNED_BYTE, 0, tess.svars.colors );
	qglTexCoordPointer( 2, GL_FLOAT, 16, tess.texCoords[0][0] );
	qglVertexPointer (3, GL_FLOAT, 16, input->xyz);

	if ( qglLockArraysEXT )
	{
		qglLockArraysEXT(0, input->numVertexes);
		GLimp_LogComment( "glLockArraysEXT\n" );
	}

	//
	// call special shade routine
	//
	R_BindAnimatedImage( &tess.xstages[0]->bundle[0] );
	GL_State( tess.xstages[0]->stateBits );
	R_DrawElements( input->numIndexes, input->indexes );

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
	if (qglUnlockArraysEXT) 
	{
		qglUnlockArraysEXT();
		GLimp_LogComment( "glUnlockArraysEXT\n" );
	}
}