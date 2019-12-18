#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* color; int width; int height; float* pixels; int /*<<< orphan*/  averageColor; scalar_t__* shader; scalar_t__* editorimage; scalar_t__* lightimage; } ;
typedef  TYPE_1__ shaderInfo_t ;
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  ColorNormalize (float*,int*) ; 
 int /*<<< orphan*/  DefaultExtension (char*,char*) ; 
 int /*<<< orphan*/ * LoadImageFile (char*,scalar_t__*) ; 
 int /*<<< orphan*/  LoadJPGBuff (int /*<<< orphan*/ *,float**,int*,int*) ; 
 int /*<<< orphan*/  LoadTGABuffer (int /*<<< orphan*/ *,float**,int*,int*) ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 int /*<<< orphan*/  VectorScale (float*,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _printf (char*,scalar_t__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* gamedir ; 
 float* malloc (int) ; 
 int /*<<< orphan*/  memset (float*,int,int) ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,scalar_t__*) ; 

__attribute__((used)) static void LoadShaderImage( shaderInfo_t *si ) {
	char			filename[1024];
	int				i, count;
	float			color[4];
  byte      *buffer;
  qboolean  bTGA = qtrue;

	// look for the lightimage if it is specified
	if ( si->lightimage[0] ) {
		sprintf( filename, "%s%s", gamedir, si->lightimage );
		DefaultExtension( filename, ".tga" );
    buffer = LoadImageFile(filename, &bTGA);
    if ( buffer != NULL) {
      goto loadTga;
    }
  }

	// look for the editorimage if it is specified
	if ( si->editorimage[0] ) {
		sprintf( filename, "%s%s", gamedir, si->editorimage );
		DefaultExtension( filename, ".tga" );
    buffer = LoadImageFile(filename, &bTGA);
    if ( buffer != NULL) {
      goto loadTga;
    }
  }

  // just try the shader name with a .tga
	// on unix, we have case sensitivity problems...
  sprintf( filename, "%s%s.tga", gamedir, si->shader );
  buffer = LoadImageFile(filename, &bTGA);
  if ( buffer != NULL) {
		goto loadTga;
	}

  sprintf( filename, "%s%s.TGA", gamedir, si->shader );
  buffer = LoadImageFile(filename, &bTGA);
  if ( buffer != NULL) {
		goto loadTga;
	}

	// couldn't load anything
	_printf("WARNING: Couldn't find image for shader %s\n", si->shader );

	si->color[0] = 1;
	si->color[1] = 1;
	si->color[2] = 1;
	si->width = 64;
	si->height = 64;
	si->pixels = malloc( si->width * si->height * 4 );
	memset ( si->pixels, 255, si->width * si->height * 4 );
	return;

	// load the image to get dimensions and color
loadTga:
  if ( bTGA) {
	  LoadTGABuffer( buffer, &si->pixels, &si->width, &si->height );
  }
  else {
#ifdef _WIN32
    LoadJPGBuff(buffer, &si->pixels, &si->width, &si->height );
#endif
  }

  free(buffer);

	count = si->width * si->height;

	VectorClear( color );
	color[ 3 ] = 0;
	for ( i = 0 ; i < count ; i++ ) {
		color[0] += si->pixels[ i * 4 + 0 ];
		color[1] += si->pixels[ i * 4 + 1 ];
		color[2] += si->pixels[ i * 4 + 2 ];
		color[3] += si->pixels[ i * 4 + 3 ];
	}
	ColorNormalize( color, si->color );
	VectorScale( color, 1.0/count, si->averageColor );
}