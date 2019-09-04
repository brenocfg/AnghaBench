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
struct TYPE_5__ {int numcomps; TYPE_1__* comps; } ;
typedef  TYPE_2__ opj_image_t ;
struct TYPE_4__ {scalar_t__ dx; scalar_t__ dy; scalar_t__ prec; int w; int h; scalar_t__* data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fwrite (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tga_writeheader (int /*<<< orphan*/ *,int,int,int,int) ; 

int imagetotga(opj_image_t * image, const char *outfile) {
	int width, height, bpp, x, y;
	bool write_alpha;
	int i;
	unsigned int alpha_channel;
	float r,g,b,a;
	unsigned char value;
	float scale;
	FILE *fdest;

	fdest = fopen(outfile, "wb");
	if (!fdest) {
		fprintf(stderr, "ERROR -> failed to open %s for writing\n", outfile);
		return 1;
	}

	for (i = 0; i < image->numcomps-1; i++)	{
		if ((image->comps[0].dx != image->comps[i+1].dx) 
			||(image->comps[0].dy != image->comps[i+1].dy) 
			||(image->comps[0].prec != image->comps[i+1].prec))	{
      fprintf(stderr, "Unable to create a tga file with such J2K image charateristics.");
      return 1;
   }
	}

	width = image->comps[0].w;
	height = image->comps[0].h; 

	// Mono with alpha, or RGB with alpha.
	write_alpha = (image->numcomps==2) || (image->numcomps==4);   

	// Write TGA header 
	bpp = write_alpha ? 32 : 24;
	if (!tga_writeheader(fdest, bpp, width , height, true))
		return 1;

	alpha_channel = image->numcomps-1; 

	scale = 255.0f / (float)((1<<image->comps[0].prec)-1);

	for (y=0; y < height; y++) {
		unsigned int index=y*width;

		for (x=0; x < width; x++, index++)	{
			r = (float)(image->comps[0].data[index]);

			if (image->numcomps>2) {
				g = (float)(image->comps[1].data[index]);
				b = (float)(image->comps[2].data[index]);
			}
			else  {// Greyscale ...
				g = r;
				b = r;
			}

			// TGA format writes BGR ...
			value = (unsigned char)(b*scale);
			fwrite(&value,1,1,fdest);

			value = (unsigned char)(g*scale);
			fwrite(&value,1,1,fdest);

			value = (unsigned char)(r*scale);
			fwrite(&value,1,1,fdest);

			if (write_alpha) {
				a = (float)(image->comps[alpha_channel].data[index]);
				value = (unsigned char)(a*scale);
				fwrite(&value,1,1,fdest);
			}
		}
	}

	return 0;
}