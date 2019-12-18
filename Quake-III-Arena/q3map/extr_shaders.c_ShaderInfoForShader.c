#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* shader; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ shaderInfo_t ;

/* Variables and functions */
 TYPE_1__* AllocShaderInfo () ; 
 int /*<<< orphan*/  LoadShaderImage (TYPE_1__*) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  StripExtension (char*) ; 
 int numShaderInfo ; 
 TYPE_1__* shaderInfo ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

shaderInfo_t	*ShaderInfoForShader( const char *shaderName ) {
	int				i;
	shaderInfo_t	*si;
	char			shader[MAX_QPATH];

	// strip off extension
	strcpy( shader, shaderName );
	StripExtension( shader );

	// search for it
	for ( i = 0 ; i < numShaderInfo ; i++ ) {
		si = &shaderInfo[ i ];
		if ( !Q_stricmp( shader, si->shader ) ) {
			if ( !si->width ) {
				LoadShaderImage( si );
			}
			return si;
		}
	}

	si = AllocShaderInfo();
	strcpy( si->shader, shader );

	LoadShaderImage( si );

	return si;
}