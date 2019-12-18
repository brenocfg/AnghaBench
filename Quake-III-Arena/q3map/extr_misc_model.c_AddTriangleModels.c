#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__* vec3_t ;
typedef  int /*<<< orphan*/  tree_t ;
typedef  int /*<<< orphan*/  entity_t ;

/* Variables and functions */
 float FloatForKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetVectorForKey (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  InsertASEModel (char const*,scalar_t__*,float,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertMD3Model (char const*,scalar_t__*,float,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 char* ValueForKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  _printf (char*,...) ; 
 int /*<<< orphan*/  c_triangleIndexes ; 
 int /*<<< orphan*/  c_triangleModels ; 
 int /*<<< orphan*/  c_triangleSurfaces ; 
 int /*<<< orphan*/  c_triangleVertexes ; 
 int /*<<< orphan*/ * entities ; 
 int num_entities ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 scalar_t__ strstr (char const*,char*) ; 

void AddTriangleModels( tree_t *tree ) {
	int			entity_num;
	entity_t	*entity;

	qprintf("----- AddTriangleModels -----\n");

	for ( entity_num=1 ; entity_num< num_entities ; entity_num++ ) {
		entity = &entities[entity_num];
	
		// convert misc_models into raw geometry
		if ( !Q_stricmp( "misc_model", ValueForKey( entity, "classname" ) ) ) {
			const char	*model;
			vec3_t	origin;
			float	angle;

			// get the angle for rotation  FIXME: support full matrix positioning
			angle = FloatForKey( entity, "angle" );

			GetVectorForKey( entity, "origin", origin );

			model = ValueForKey( entity, "model" );
			if ( !model[0] ) {
				_printf("WARNING: misc_model at %i %i %i without a model key\n", (int)origin[0],
					(int)origin[1], (int)origin[2] );
				continue;
			}
			if ( strstr( model, ".md3" ) || strstr( model, ".MD3" ) ) {
				InsertMD3Model( model, origin, angle, tree );
				continue;
			}
			if ( strstr( model, ".ase" ) || strstr( model, ".ASE" ) ) {
				InsertASEModel( model, origin, angle, tree );
				continue;
			}
			_printf( "Unknown misc_model type: %s\n", model );
			continue;
		}
	}

	qprintf( "%5i triangle models\n", c_triangleModels );
	qprintf( "%5i triangle surfaces\n", c_triangleSurfaces );
	qprintf( "%5i triangle vertexes\n", c_triangleVertexes );
	qprintf( "%5i triangle indexes\n", c_triangleIndexes );
}