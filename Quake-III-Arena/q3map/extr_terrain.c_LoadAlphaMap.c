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
typedef  int byte ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,...) ; 
 int /*<<< orphan*/  ExpandGamePath (char const*) ; 
 int /*<<< orphan*/  ExtractFileExtension (char const*,char*) ; 
 int /*<<< orphan*/  Load256Image (int /*<<< orphan*/ ,int**,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  Load32BitImage (int /*<<< orphan*/ ,int**,int*,int*) ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 char* ValueForKey (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert (int*) ; 
 int atoi (char*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  mapent ; 

byte *LoadAlphaMap( int *num_layers, int *alphawidth, int *alphaheight ) {
	int			*alphamap32;
	byte		*alphamap;
	const char	*alphamapname;
	char		ext[ 128 ];
	int			width;
	int			height;
	int			layers;
	int			size;
	int			i;

	assert( alphawidth );
	assert( alphaheight );
	assert( num_layers );

	layers = atoi( ValueForKey( mapent, "layers" ) );
	if ( layers < 1 ) {
		Error ("SetTerrainTextures: invalid value for 'layers' (%d)", layers );
	}

	alphamapname = ValueForKey( mapent, "alphamap" );
	if ( !alphamapname[ 0 ] ) {
		Error ("LoadAlphaMap: No alphamap specified on terrain" );
	}

	ExtractFileExtension( alphamapname, ext);
	if ( !Q_stricmp( ext, "tga" ) ) {
		Load32BitImage( ExpandGamePath( alphamapname ), &alphamap32, &width, &height );

		size = width * height;
		alphamap = malloc( size );
		for( i = 0; i < size; i++ ) {
			alphamap[ i ] = ( ( alphamap32[ i ] & 0xff ) * layers ) / 256;
			if ( alphamap[ i ] >= layers ) {
				alphamap[ i ] = layers - 1;
			}
		}
	} else {
		Load256Image( ExpandGamePath( alphamapname ), &alphamap, NULL, &width, &height );
		size = width * height;
		for( i = 0; i < size; i++ ) {
			if ( alphamap[ i ] >= layers ) {
				alphamap[ i ] = layers - 1;
			}
		}
	}

	if ( ( width < 2 ) || ( height < 2 ) ) {
		Error ("LoadAlphaMap: alphamap width/height must be at least 2x2." );
	}

	*num_layers		= layers;
	*alphawidth		= width;
	*alphaheight	= height;

	return alphamap;
}