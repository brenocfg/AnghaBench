#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  contents; int /*<<< orphan*/  surfaceFlags; } ;
typedef  TYPE_1__ shaderInfo_t ;
struct TYPE_5__ {int /*<<< orphan*/  contentFlags; int /*<<< orphan*/  surfaceFlags; int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_MAP_SHADERS ; 
 int /*<<< orphan*/  Q_stricmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ShaderInfoForShader (char const*) ; 
 TYPE_2__* dshaders ; 
 int numShaders ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

int	EmitShader( const char *shader ) {
	int				i;
	shaderInfo_t	*si;

	if ( !shader ) {
		shader = "noshader";
	}

	for ( i = 0 ; i < numShaders ; i++ ) {
		if ( !Q_stricmp( shader, dshaders[i].shader ) ) {
			return i;
		}
	}

	if ( i == MAX_MAP_SHADERS ) {
		Error( "MAX_MAP_SHADERS" );
	}
	numShaders++;
	strcpy( dshaders[i].shader, shader );

	si = ShaderInfoForShader( shader );
	dshaders[i].surfaceFlags = si->surfaceFlags;
	dshaders[i].contentFlags = si->contents;

	return i;
}