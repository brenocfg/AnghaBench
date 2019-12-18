#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
typedef  int /*<<< orphan*/  tree_t ;
struct TYPE_11__ {float* xyz; int normal; } ;
typedef  TYPE_1__ md3XyzNormal_t ;
struct TYPE_12__ {int /*<<< orphan*/ * indexes; } ;
typedef  TYPE_2__ md3Triangle_t ;
struct TYPE_13__ {int ofsShaders; int numVerts; int numTriangles; int ofsTriangles; int ofsSt; int ofsXyzNormals; int ofsEnd; } ;
typedef  TYPE_3__ md3Surface_t ;
struct TYPE_14__ {int /*<<< orphan*/ * st; } ;
typedef  TYPE_4__ md3St_t ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ md3Shader_t ;
struct TYPE_16__ {int numSurfaces; int ofsSurfaces; } ;
typedef  TYPE_6__ md3Header_t ;
struct TYPE_17__ {int numVerts; int numIndexes; int lightmapNum; int fogNum; TYPE_8__* verts; int /*<<< orphan*/ * indexes; int /*<<< orphan*/  shaderInfo; int /*<<< orphan*/  miscModel; } ;
typedef  TYPE_7__ mapDrawSurface_t ;
struct TYPE_18__ {int* color; float* xyz; float* normal; scalar_t__* lightmap; int /*<<< orphan*/ * st; } ;
typedef  TYPE_8__ drawVert_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 TYPE_7__* AllocDrawSurf () ; 
 TYPE_6__* LoadModel (char const*) ; 
 float MD3_XYZ_SCALE ; 
 float Q_PI ; 
 int /*<<< orphan*/  ShaderInfoForShader (int /*<<< orphan*/ ) ; 
 int c_triangleIndexes ; 
 int /*<<< orphan*/  c_triangleModels ; 
 int c_triangleSurfaces ; 
 int c_triangleVertexes ; 
 float cos (float) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  qtrue ; 
 float sin (float) ; 

void InsertMD3Model( const char *modelName, vec3_t origin, float angle, tree_t *tree ) {
	int					i, j;
	md3Header_t			*md3;
	md3Surface_t		*surf;
	md3Shader_t			*shader;
	md3Triangle_t		*tri;
	md3St_t				*st;
	md3XyzNormal_t		*xyz;
	drawVert_t			*outv;
	float				lat, lng;
	float				angleCos, angleSin;
	mapDrawSurface_t	*out;
	vec3_t				temp;

	angle = angle / 180 * Q_PI;
	angleCos = cos( angle );
	angleSin = sin( angle );

	// load the model
	md3 = LoadModel( modelName );
	if ( !md3 ) {
		return;
	}

	// each md3 surface will become a new bsp surface

	c_triangleModels++;
	c_triangleSurfaces += md3->numSurfaces;

	// expand, translate, and rotate the vertexes
	// swap all the surfaces
	surf = (md3Surface_t *) ( (byte *)md3 + md3->ofsSurfaces );
	for ( i = 0 ; i < md3->numSurfaces ; i++) {
		// allocate a surface
		out = AllocDrawSurf();
		out->miscModel = qtrue;

        shader = (md3Shader_t *) ( (byte *)surf + surf->ofsShaders );

		out->shaderInfo = ShaderInfoForShader( shader->name );

		out->numVerts = surf->numVerts;
		out->verts = malloc( out->numVerts * sizeof( out->verts[0] ) );

		out->numIndexes = surf->numTriangles * 3;
		out->indexes = malloc( out->numIndexes * sizeof( out->indexes[0] ) );

		out->lightmapNum = -1;
		out->fogNum = -1;

		// emit the indexes
		c_triangleIndexes += surf->numTriangles * 3;
		tri = (md3Triangle_t *) ( (byte *)surf + surf->ofsTriangles );
		for ( j = 0 ; j < surf->numTriangles ; j++, tri++ ) {
			out->indexes[j*3+0] = tri->indexes[0];
			out->indexes[j*3+1] = tri->indexes[1];
			out->indexes[j*3+2] = tri->indexes[2];
		}

		// emit the vertexes
        st = (md3St_t *) ( (byte *)surf + surf->ofsSt );
        xyz = (md3XyzNormal_t *) ( (byte *)surf + surf->ofsXyzNormals );

		c_triangleVertexes += surf->numVerts;
		for ( j = 0 ; j < surf->numVerts ; j++, st++, xyz++ ) {
			outv = &out->verts[ j ];

			outv->st[0] = st->st[0];
			outv->st[1] = st->st[1];

			outv->lightmap[0] = 0;
			outv->lightmap[1] = 0;

			// the colors will be set by the lighting pass
			outv->color[0] = 255;
			outv->color[1] = 255;
			outv->color[2] = 255;
			outv->color[3] = 255;

			outv->xyz[0] = origin[0] + MD3_XYZ_SCALE * ( xyz->xyz[0] * angleCos - xyz->xyz[1] * angleSin );
			outv->xyz[1] = origin[1] + MD3_XYZ_SCALE * ( xyz->xyz[0] * angleSin +  xyz->xyz[1] * angleCos );
			outv->xyz[2] = origin[2] + MD3_XYZ_SCALE * ( xyz->xyz[2] );

			// decode the lat/lng normal to a 3 float normal
			lat = ( xyz->normal >> 8 ) & 0xff;
			lng = ( xyz->normal & 0xff );
			lat *= Q_PI/128;
			lng *= Q_PI/128;

			temp[0] = cos(lat) * sin(lng);
			temp[1] = sin(lat) * sin(lng);
			temp[2] = cos(lng);

			// rotate the normal
			outv->normal[0] = temp[0] * angleCos - temp[1] * angleSin;
			outv->normal[1] = temp[0] * angleSin +  temp[1] * angleCos;
			outv->normal[2] = temp[2];
		}

		// find the next surface
		surf = (md3Surface_t *)( (byte *)surf + surf->ofsEnd );
	}

}