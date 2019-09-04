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
struct TYPE_2__ {unsigned int pixel_depth; unsigned int image_width; unsigned int image_height; int id_length; int image_type; int image_desc; int colour_map_length; int colour_map_entry_size; } ;
typedef  TYPE_1__ tga_header ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

int tga_readheader(FILE *fp, unsigned int *bits_per_pixel, 
	unsigned int *width, unsigned int *height, int *flip_image)
{
	int palette_size;
	tga_header tga ;

	if (!bits_per_pixel || !width || !height || !flip_image)
		return 0;
	
	// Read TGA header
	fread((unsigned char*)&tga, sizeof(tga_header), 1, fp);

	*bits_per_pixel = tga.pixel_depth;
	
	*width  = tga.image_width;
	*height = tga.image_height ;

	// Ignore tga identifier, if present ...
	if (tga.id_length)
	{
		unsigned char *id = (unsigned char *) malloc(tga.id_length);
		fread(id, tga.id_length, 1, fp);
		free(id);  
	}

	// Test for compressed formats ... not yet supported ...
	// Note :-  9 - RLE encoded palettized.
	//	  	   10 - RLE encoded RGB.
	if (tga.image_type > 8)
	{
		fprintf(stderr, "Sorry, compressed tga files are not currently supported.\n");
		return 0 ;
	}

	*flip_image = !(tga.image_desc & 32);

	// Palettized formats are not yet supported, skip over the palette, if present ... 
	palette_size = tga.colour_map_length * (tga.colour_map_entry_size/8);
	
	if (palette_size>0)
	{
		fprintf(stderr, "File contains a palette - not yet supported.");
		fseek(fp, palette_size, SEEK_CUR);
	}
	return 1;
}