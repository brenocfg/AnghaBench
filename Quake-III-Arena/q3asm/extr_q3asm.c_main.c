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
 int /*<<< orphan*/  Assemble () ; 
 int /*<<< orphan*/  Error (char*,...) ; 
 double I_FloatTime () ; 
 int /*<<< orphan*/  InitTables () ; 
 int /*<<< orphan*/  ParseOptionFile (char*) ; 
 int /*<<< orphan*/ * asmFileNames ; 
 int /*<<< orphan*/  copystring (char*) ; 
 size_t numAsmFiles ; 
 int /*<<< orphan*/  outputFilename ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int main( int argc, char **argv ) {
	int			i;
	double		start, end;

//	_chdir( "/quake3/jccode/cgame/lccout" );	// hack for vc profiler

	if ( argc < 2 ) {
		Error( "usage: q3asm [-o output] <files> or q3asm -f <listfile>\n" );
	}

	start = I_FloatTime ();
	InitTables();

	// default filename is "q3asm"
	strcpy( outputFilename, "q3asm" );
	numAsmFiles = 0;	

	for ( i = 1 ; i < argc ; i++ ) {
		if ( argv[i][0] != '-' ) {
			break;
		}
		if ( !strcmp( argv[i], "-o" ) ) {
			if ( i == argc - 1 ) {
				Error( "-o must preceed a filename" );
			}
			strcpy( outputFilename, argv[ i+1 ] );
			i++;
			continue;
		}

		if ( !strcmp( argv[i], "-f" ) ) {
			if ( i == argc - 1 ) {
				Error( "-f must preceed a filename" );
			}
			ParseOptionFile( argv[ i+1 ] );
			i++;
			continue;
		}
		Error( "Unknown option: %s", argv[i] );
	}

	// the rest of the command line args are asm files
	for ( ; i < argc ; i++ ) {
		asmFileNames[ numAsmFiles ] = copystring( argv[ i ] );
		numAsmFiles++;
	}

	Assemble();

	end = I_FloatTime ();
	printf ("%5.0f seconds elapsed\n", end-start);

	return 0;
}