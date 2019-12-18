#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_10__* bundle; int /*<<< orphan*/  stateBits; } ;
typedef  TYPE_2__ shaderStage_t ;
struct TYPE_16__ {int /*<<< orphan*/ * texcoords; int /*<<< orphan*/  colors; } ;
struct TYPE_18__ {int /*<<< orphan*/  indexes; int /*<<< orphan*/  numIndexes; TYPE_1__ svars; } ;
typedef  TYPE_3__ shaderCommands_t ;
struct TYPE_24__ {scalar_t__ hardwareType; } ;
struct TYPE_23__ {scalar_t__ integer; } ;
struct TYPE_22__ {int /*<<< orphan*/  integer; } ;
struct TYPE_21__ {scalar_t__ integer; } ;
struct TYPE_20__ {TYPE_2__** xstages; } ;
struct TYPE_19__ {int /*<<< orphan*/  whiteImage; } ;
struct TYPE_15__ {scalar_t__* image; scalar_t__ vertexLightmap; scalar_t__ isLightmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ComputeColors (TYPE_2__*) ; 
 int /*<<< orphan*/  ComputeTexCoords (TYPE_2__*) ; 
 int /*<<< orphan*/  DrawMultitextured (TYPE_3__*,int) ; 
 scalar_t__ GLHW_PERMEDIA2 ; 
 int /*<<< orphan*/  GL_Bind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_COLOR_ARRAY ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_State (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int MAX_SHADER_STAGES ; 
 int /*<<< orphan*/  R_BindAnimatedImage (TYPE_10__*) ; 
 int /*<<< orphan*/  R_DrawElements (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ glConfig ; 
 int /*<<< orphan*/  qglColorPointer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglTexCoordPointer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* r_lightmap ; 
 TYPE_7__* r_uiFullScreen ; 
 TYPE_6__* r_vertexLight ; 
 int /*<<< orphan*/  setArraysOnce ; 
 TYPE_5__ tess ; 
 TYPE_4__ tr ; 

__attribute__((used)) static void RB_IterateStagesGeneric( shaderCommands_t *input )
{
	int stage;

	for ( stage = 0; stage < MAX_SHADER_STAGES; stage++ )
	{
		shaderStage_t *pStage = tess.xstages[stage];

		if ( !pStage )
		{
			break;
		}

		ComputeColors( pStage );
		ComputeTexCoords( pStage );

		if ( !setArraysOnce )
		{
			qglEnableClientState( GL_COLOR_ARRAY );
			qglColorPointer( 4, GL_UNSIGNED_BYTE, 0, input->svars.colors );
		}

		//
		// do multitexture
		//
		if ( pStage->bundle[1].image[0] != 0 )
		{
			DrawMultitextured( input, stage );
		}
		else
		{
			if ( !setArraysOnce )
			{
				qglTexCoordPointer( 2, GL_FLOAT, 0, input->svars.texcoords[0] );
			}

			//
			// set state
			//
			if ( pStage->bundle[0].vertexLightmap && ( (r_vertexLight->integer && !r_uiFullScreen->integer) || glConfig.hardwareType == GLHW_PERMEDIA2 ) && r_lightmap->integer )
			{
				GL_Bind( tr.whiteImage );
			}
			else 
				R_BindAnimatedImage( &pStage->bundle[0] );

			GL_State( pStage->stateBits );

			//
			// draw
			//
			R_DrawElements( input->numIndexes, input->indexes );
		}
		// allow skipping out to show just lightmaps during development
		if ( r_lightmap->integer && ( pStage->bundle[0].isLightmap || pStage->bundle[1].isLightmap || pStage->bundle[0].vertexLightmap ) )
		{
			break;
		}
	}
}