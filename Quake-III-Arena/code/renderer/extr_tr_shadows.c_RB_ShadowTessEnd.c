#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_8__ {scalar_t__ isMirror; } ;
struct TYPE_12__ {TYPE_2__ viewParms; TYPE_1__* currentEntity; } ;
struct TYPE_11__ {int stencilBits; } ;
struct TYPE_10__ {int numVertexes; float** xyz; int numIndexes; int* indexes; } ;
struct TYPE_9__ {int /*<<< orphan*/  whiteImage; } ;
struct TYPE_7__ {int /*<<< orphan*/  lightDir; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GLS_DSTBLEND_ZERO ; 
 int GLS_SRCBLEND_ONE ; 
 int /*<<< orphan*/  GL_ALWAYS ; 
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_Bind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_DECR ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GL_INCR ; 
 int /*<<< orphan*/  GL_KEEP ; 
 int /*<<< orphan*/  GL_STENCIL_TEST ; 
 int /*<<< orphan*/  GL_State (int) ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  R_AddEdgeDef (int,int,int) ; 
 int /*<<< orphan*/  R_RenderShadowEdges () ; 
 int SHADER_MAX_VERTEXES ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (float*,int,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,int /*<<< orphan*/ ) ; 
 TYPE_6__ backEnd ; 
 int* facing ; 
 TYPE_5__ glConfig ; 
 int /*<<< orphan*/  numEdgeDefs ; 
 int /*<<< orphan*/  qglColor3f (float,float,float) ; 
 int /*<<< orphan*/  qglColorMask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglCullFace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglStencilFunc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qglStencilOp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ tess ; 
 TYPE_3__ tr ; 

void RB_ShadowTessEnd( void ) {
	int		i;
	int		numTris;
	vec3_t	lightDir;

	// we can only do this if we have enough space in the vertex buffers
	if ( tess.numVertexes >= SHADER_MAX_VERTEXES / 2 ) {
		return;
	}

	if ( glConfig.stencilBits < 4 ) {
		return;
	}

	VectorCopy( backEnd.currentEntity->lightDir, lightDir );

	// project vertexes away from light direction
	for ( i = 0 ; i < tess.numVertexes ; i++ ) {
		VectorMA( tess.xyz[i], -512, lightDir, tess.xyz[i+tess.numVertexes] );
	}

	// decide which triangles face the light
	Com_Memset( numEdgeDefs, 0, 4 * tess.numVertexes );

	numTris = tess.numIndexes / 3;
	for ( i = 0 ; i < numTris ; i++ ) {
		int		i1, i2, i3;
		vec3_t	d1, d2, normal;
		float	*v1, *v2, *v3;
		float	d;

		i1 = tess.indexes[ i*3 + 0 ];
		i2 = tess.indexes[ i*3 + 1 ];
		i3 = tess.indexes[ i*3 + 2 ];

		v1 = tess.xyz[ i1 ];
		v2 = tess.xyz[ i2 ];
		v3 = tess.xyz[ i3 ];

		VectorSubtract( v2, v1, d1 );
		VectorSubtract( v3, v1, d2 );
		CrossProduct( d1, d2, normal );

		d = DotProduct( normal, lightDir );
		if ( d > 0 ) {
			facing[ i ] = 1;
		} else {
			facing[ i ] = 0;
		}

		// create the edges
		R_AddEdgeDef( i1, i2, facing[ i ] );
		R_AddEdgeDef( i2, i3, facing[ i ] );
		R_AddEdgeDef( i3, i1, facing[ i ] );
	}

	// draw the silhouette edges

	GL_Bind( tr.whiteImage );
	qglEnable( GL_CULL_FACE );
	GL_State( GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO );
	qglColor3f( 0.2f, 0.2f, 0.2f );

	// don't write to the color buffer
	qglColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );

	qglEnable( GL_STENCIL_TEST );
	qglStencilFunc( GL_ALWAYS, 1, 255 );

	// mirrors have the culling order reversed
	if ( backEnd.viewParms.isMirror ) {
		qglCullFace( GL_FRONT );
		qglStencilOp( GL_KEEP, GL_KEEP, GL_INCR );

		R_RenderShadowEdges();

		qglCullFace( GL_BACK );
		qglStencilOp( GL_KEEP, GL_KEEP, GL_DECR );

		R_RenderShadowEdges();
	} else {
		qglCullFace( GL_BACK );
		qglStencilOp( GL_KEEP, GL_KEEP, GL_INCR );

		R_RenderShadowEdges();

		qglCullFace( GL_FRONT );
		qglStencilOp( GL_KEEP, GL_KEEP, GL_DECR );

		R_RenderShadowEdges();
	}


	// reenable writing to the color buffer
	qglColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
}