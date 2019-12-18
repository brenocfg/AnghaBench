#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_4__* bundle; } ;
typedef  TYPE_6__ shaderStage_t ;
struct TYPE_21__ {TYPE_3__* currentEntity; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {void**** texcoords; } ;
struct TYPE_19__ {int numVertexes; TYPE_1__* shader; TYPE_5__ svars; int /*<<< orphan*/ * xyz; void**** texCoords; } ;
struct TYPE_16__ {int tcGen; int numTexMods; TYPE_10__* texMods; int /*<<< orphan*/ * tcGenVectors; } ;
struct TYPE_14__ {int /*<<< orphan*/  shaderTexCoord; } ;
struct TYPE_15__ {TYPE_2__ e; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int type; int /*<<< orphan*/  rotateSpeed; int /*<<< orphan*/  wave; int /*<<< orphan*/  scale; int /*<<< orphan*/  scroll; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (void***,int /*<<< orphan*/ ,int) ; 
 void* DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int NUM_TEXTURE_BUNDLES ; 
 int /*<<< orphan*/  RB_CalcEnvironmentTexCoords (float*) ; 
 int /*<<< orphan*/  RB_CalcFogTexCoords (float*) ; 
 int /*<<< orphan*/  RB_CalcRotateTexCoords (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  RB_CalcScaleTexCoords (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  RB_CalcScrollTexCoords (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  RB_CalcStretchTexCoords (int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  RB_CalcTransformTexCoords (TYPE_10__*,float*) ; 
 int /*<<< orphan*/  RB_CalcTurbulentTexCoords (int /*<<< orphan*/ *,float*) ; 
#define  TCGEN_BAD 142 
#define  TCGEN_ENVIRONMENT_MAPPED 141 
#define  TCGEN_FOG 140 
#define  TCGEN_IDENTITY 139 
#define  TCGEN_LIGHTMAP 138 
#define  TCGEN_TEXTURE 137 
#define  TCGEN_VECTOR 136 
#define  TMOD_ENTITY_TRANSLATE 135 
#define  TMOD_NONE 134 
#define  TMOD_ROTATE 133 
#define  TMOD_SCALE 132 
#define  TMOD_SCROLL 131 
#define  TMOD_STRETCH 130 
#define  TMOD_TRANSFORM 129 
#define  TMOD_TURBULENT 128 
 int TR_MAX_TEXMODS ; 
 TYPE_9__ backEnd ; 
 TYPE_8__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_7__ tess ; 

__attribute__((used)) static void ComputeTexCoords( shaderStage_t *pStage ) {
	int		i;
	int		b;

	for ( b = 0; b < NUM_TEXTURE_BUNDLES; b++ ) {
		int tm;

		//
		// generate the texture coordinates
		//
		switch ( pStage->bundle[b].tcGen )
		{
		case TCGEN_IDENTITY:
			Com_Memset( tess.svars.texcoords[b], 0, sizeof( float ) * 2 * tess.numVertexes );
			break;
		case TCGEN_TEXTURE:
			for ( i = 0 ; i < tess.numVertexes ; i++ ) {
				tess.svars.texcoords[b][i][0] = tess.texCoords[i][0][0];
				tess.svars.texcoords[b][i][1] = tess.texCoords[i][0][1];
			}
			break;
		case TCGEN_LIGHTMAP:
			for ( i = 0 ; i < tess.numVertexes ; i++ ) {
				tess.svars.texcoords[b][i][0] = tess.texCoords[i][1][0];
				tess.svars.texcoords[b][i][1] = tess.texCoords[i][1][1];
			}
			break;
		case TCGEN_VECTOR:
			for ( i = 0 ; i < tess.numVertexes ; i++ ) {
				tess.svars.texcoords[b][i][0] = DotProduct( tess.xyz[i], pStage->bundle[b].tcGenVectors[0] );
				tess.svars.texcoords[b][i][1] = DotProduct( tess.xyz[i], pStage->bundle[b].tcGenVectors[1] );
			}
			break;
		case TCGEN_FOG:
			RB_CalcFogTexCoords( ( float * ) tess.svars.texcoords[b] );
			break;
		case TCGEN_ENVIRONMENT_MAPPED:
			RB_CalcEnvironmentTexCoords( ( float * ) tess.svars.texcoords[b] );
			break;
		case TCGEN_BAD:
			return;
		}

		//
		// alter texture coordinates
		//
		for ( tm = 0; tm < pStage->bundle[b].numTexMods ; tm++ ) {
			switch ( pStage->bundle[b].texMods[tm].type )
			{
			case TMOD_NONE:
				tm = TR_MAX_TEXMODS;		// break out of for loop
				break;

			case TMOD_TURBULENT:
				RB_CalcTurbulentTexCoords( &pStage->bundle[b].texMods[tm].wave, 
						                 ( float * ) tess.svars.texcoords[b] );
				break;

			case TMOD_ENTITY_TRANSLATE:
				RB_CalcScrollTexCoords( backEnd.currentEntity->e.shaderTexCoord,
									 ( float * ) tess.svars.texcoords[b] );
				break;

			case TMOD_SCROLL:
				RB_CalcScrollTexCoords( pStage->bundle[b].texMods[tm].scroll,
										 ( float * ) tess.svars.texcoords[b] );
				break;

			case TMOD_SCALE:
				RB_CalcScaleTexCoords( pStage->bundle[b].texMods[tm].scale,
									 ( float * ) tess.svars.texcoords[b] );
				break;
			
			case TMOD_STRETCH:
				RB_CalcStretchTexCoords( &pStage->bundle[b].texMods[tm].wave, 
						               ( float * ) tess.svars.texcoords[b] );
				break;

			case TMOD_TRANSFORM:
				RB_CalcTransformTexCoords( &pStage->bundle[b].texMods[tm],
						                 ( float * ) tess.svars.texcoords[b] );
				break;

			case TMOD_ROTATE:
				RB_CalcRotateTexCoords( pStage->bundle[b].texMods[tm].rotateSpeed,
										( float * ) tess.svars.texcoords[b] );
				break;

			default:
				ri.Error( ERR_DROP, "ERROR: unknown texmod '%d' in shader '%s'\n", pStage->bundle[b].texMods[tm].type, tess.shader->name );
				break;
			}
		}
	}
}