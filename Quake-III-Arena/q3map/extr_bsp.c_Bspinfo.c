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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultExtension (char*,char*) ; 
 int /*<<< orphan*/  LoadBSPFile (char*) ; 
 int /*<<< orphan*/  PrintBSPFileSizes () ; 
 int Q_filelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _printf (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void Bspinfo( int count, char **fileNames ) {
	int		i;
	char	source[1024];
	int			size;
	FILE		*f;

	if ( count < 1 ) {
		_printf( "No files to dump info for.\n");
		return;
	}

	for ( i = 0 ; i < count ; i++ ) {
		_printf ("---------------------\n");
		strcpy (source, fileNames[ i ] );
		DefaultExtension (source, ".bsp");
		f = fopen (source, "rb");
		if (f)
		{
			size = Q_filelength (f);
			fclose (f);
		}
		else
			size = 0;
		_printf ("%s: %i\n", source, size);
		
		LoadBSPFile (source);		
		PrintBSPFileSizes ();
		_printf ("---------------------\n");
	}
}