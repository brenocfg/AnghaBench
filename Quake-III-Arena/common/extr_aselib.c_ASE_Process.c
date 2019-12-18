#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t currentObject; TYPE_1__* objects; scalar_t__ grabAnims; } ;
struct TYPE_3__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASE_FreeGeomObject (size_t) ; 
 scalar_t__ ASE_GetToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASE_KeyGEOMOBJECT ; 
 int /*<<< orphan*/  ASE_KeyMATERIAL_LIST ; 
 int /*<<< orphan*/  ASE_ParseBracedBlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASE_SkipEnclosingBraces () ; 
 int /*<<< orphan*/  ASE_SkipRestOfLine () ; 
 int /*<<< orphan*/  CollapseObjects () ; 
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_ASE_OBJECTS ; 
 int /*<<< orphan*/  VERBOSE (char*) ; 
 TYPE_2__ ase ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  qfalse ; 
 char* s_token ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strstr (scalar_t__,char*) ; 

__attribute__((used)) static void ASE_Process( void )
{
	while ( ASE_GetToken( qfalse ) )
	{
		if ( !strcmp( s_token, "*3DSMAX_ASCIIEXPORT" ) ||
			 !strcmp( s_token, "*COMMENT" ) )
		{
			ASE_SkipRestOfLine();
		}
		else if ( !strcmp( s_token, "*SCENE" ) )
			ASE_SkipEnclosingBraces();
		else if ( !strcmp( s_token, "*MATERIAL_LIST" ) )
		{
			VERBOSE( ("MATERIAL_LIST\n") );

			ASE_ParseBracedBlock( ASE_KeyMATERIAL_LIST );
		}
		else if ( !strcmp( s_token, "*GEOMOBJECT" ) )
		{
			VERBOSE( ("GEOMOBJECT" ) );

			ASE_ParseBracedBlock( ASE_KeyGEOMOBJECT );

			if ( strstr( ase.objects[ase.currentObject].name, "Bip" ) ||
				 strstr( ase.objects[ase.currentObject].name, "ignore_" ) )
			{
				ASE_FreeGeomObject( ase.currentObject );
				VERBOSE( ( "(discarding BIP/ignore object)\n" ) );
			}
			else if ( ( strstr( ase.objects[ase.currentObject].name, "h_" ) != ase.objects[ase.currentObject].name ) &&
				      ( strstr( ase.objects[ase.currentObject].name, "l_" ) != ase.objects[ase.currentObject].name ) &&
					  ( strstr( ase.objects[ase.currentObject].name, "u_" ) != ase.objects[ase.currentObject].name ) &&
					  ( strstr( ase.objects[ase.currentObject].name, "tag" ) != ase.objects[ase.currentObject].name ) &&
					  ase.grabAnims )
			{
				VERBOSE( ( "(ignoring improperly labeled object '%s')\n", ase.objects[ase.currentObject].name ) );
				ASE_FreeGeomObject( ase.currentObject );
			}
			else
			{
				if ( ++ase.currentObject == MAX_ASE_OBJECTS )
				{
					Error( "Too many GEOMOBJECTs" );
				}
			}
		}
		else if ( s_token[0] )
		{
			printf( "Unknown token '%s'\n", s_token );
		}
	}

	if ( !ase.currentObject )
		Error( "No animation data!" );

	CollapseObjects();
}