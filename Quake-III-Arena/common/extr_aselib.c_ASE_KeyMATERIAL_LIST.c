#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ numMaterials; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASE_GetToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASE_KeyMATERIAL ; 
 int /*<<< orphan*/  ASE_ParseBracedBlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ MAX_ASE_MATERIALS ; 
 int /*<<< orphan*/  VERBOSE (char*) ; 
 TYPE_1__ ase ; 
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  s_token ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void ASE_KeyMATERIAL_LIST( const char *token )
{
	if ( !strcmp( token, "*MATERIAL_COUNT" ) )
	{
		ASE_GetToken( qfalse );
		VERBOSE( ( "..num materials: %s\n", s_token ) );
		if ( atoi( s_token ) > MAX_ASE_MATERIALS )
		{
			Error( "Too many materials!" );
		}
		ase.numMaterials = 0;
	}
	else if ( !strcmp( token, "*MATERIAL" ) )
	{
		VERBOSE( ( "..material %d ", ase.numMaterials ) );
		ASE_ParseBracedBlock( ASE_KeyMATERIAL );
		ase.numMaterials++;
	}
}