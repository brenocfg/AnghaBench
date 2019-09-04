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
struct TYPE_3__ {int pixel_depth; int image_width; int image_height; int image_type; int image_desc; } ;
typedef  TYPE_1__ tga_header ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int tga_writeheader(FILE *fp, int bits_per_pixel, int width, int height, 
	bool flip_image)
{
	tga_header tga;

	if (!bits_per_pixel || !width || !height)
		return 0;

	memset(&tga, 0, sizeof(tga_header));

	tga.pixel_depth = bits_per_pixel;
	tga.image_width  = width;
	tga.image_height = height;
	tga.image_type = 2; // Uncompressed.
	tga.image_desc = 8; // 8 bits per component.

	if (flip_image)
		tga.image_desc |= 32;

	// Write TGA header
	fwrite((unsigned char*)&tga, sizeof(tga_header), 1, fp);

	return 1;
}