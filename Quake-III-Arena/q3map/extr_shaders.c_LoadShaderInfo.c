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

/* Variables and functions */
 int /*<<< orphan*/  GetToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadScriptFile (char*) ; 
 int /*<<< orphan*/  MAX_OS_PATH ; 
 int MAX_SHADER_FILES ; 
 int /*<<< orphan*/  ParseShaderFile (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* gamedir ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numShaderInfo ; 
 int /*<<< orphan*/  qprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  token ; 

void LoadShaderInfo( void ) {
	char			filename[1024];
	int				i;
	char			*shaderFiles[MAX_SHADER_FILES];
	int				numShaderFiles;

	sprintf( filename, "%sscripts/shaderlist.txt", gamedir );
	LoadScriptFile( filename );

	numShaderFiles = 0;
	while ( 1 ) {
		if ( !GetToken( qtrue ) ) {
			break;
		}
    shaderFiles[numShaderFiles] = malloc(MAX_OS_PATH);
		strcpy( shaderFiles[ numShaderFiles ], token );
		numShaderFiles++;
	}

	for ( i = 0 ; i < numShaderFiles ; i++ ) {
		sprintf( filename, "%sscripts/%s.shader", gamedir, shaderFiles[i] );
		ParseShaderFile( filename );
    free(shaderFiles[i]);
	}

	qprintf( "%5i shaderInfo\n", numShaderInfo);
}