#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* comps; scalar_t__ y1; scalar_t__ x1; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_2__ opj_image_t ;
struct TYPE_12__ {int prec; int bpp; int dx; int dy; int w; int h; scalar_t__ sgnd; } ;
typedef  TYPE_3__ opj_image_cmptparm_t ;
struct TYPE_13__ {int subsampling_dx; int subsampling_dy; scalar_t__ image_offset_y0; scalar_t__ image_offset_x0; } ;
typedef  TYPE_4__ opj_cparameters_t ;
struct TYPE_10__ {unsigned int* data; } ;
typedef  int /*<<< orphan*/  OPJ_COLOR_SPACE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CLRSPC_GRAY ; 
 int /*<<< orphan*/  CLRSPC_SRGB ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscanf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* opj_image_create (int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

opj_image_t* pnmtoimage(const char *filename, opj_cparameters_t *parameters) {
	int subsampling_dx = parameters->subsampling_dx;
	int subsampling_dy = parameters->subsampling_dy;

	FILE *f = NULL;
	int i, compno, numcomps, w, h;
	OPJ_COLOR_SPACE color_space;
	opj_image_cmptparm_t cmptparm[3];	/* maximum of 3 components */
	opj_image_t * image = NULL;
	char value;
	
	f = fopen(filename, "rb");
	if (!f) {
		fprintf(stderr, "Failed to open %s for reading !!\n", filename);
		return 0;
	}

	if (fgetc(f) != 'P')
		return 0;
	value = fgetc(f);

		switch(value) {
			case '2':	/* greyscale image type */
			case '5':
				numcomps = 1;
				color_space = CLRSPC_GRAY;
				break;
				
			case '3':	/* RGB image type */
			case '6':
				numcomps = 3;
				color_space = CLRSPC_SRGB;
				break;
				
			default:
				fclose(f);
				return NULL;
		}
		
		fgetc(f);
		
		/* skip comments */
		while(fgetc(f) == '#') while(fgetc(f) != '\n');
		
		fseek(f, -1, SEEK_CUR);
		fscanf(f, "%d %d\n255", &w, &h);			
		fgetc(f);	/* <cr><lf> */
		
	/* initialize image components */
	memset(&cmptparm[0], 0, 3 * sizeof(opj_image_cmptparm_t));
	for(i = 0; i < numcomps; i++) {
		cmptparm[i].prec = 8;
		cmptparm[i].bpp = 8;
		cmptparm[i].sgnd = 0;
		cmptparm[i].dx = subsampling_dx;
		cmptparm[i].dy = subsampling_dy;
		cmptparm[i].w = w;
		cmptparm[i].h = h;
	}
	/* create the image */
	image = opj_image_create(numcomps, &cmptparm[0], color_space);
	if(!image) {
		fclose(f);
		return NULL;
	}

	/* set image offset and reference grid */
	image->x0 = parameters->image_offset_x0;
	image->y0 = parameters->image_offset_y0;
	image->x1 = parameters->image_offset_x0 + (w - 1) *	subsampling_dx + 1;
	image->y1 = parameters->image_offset_y0 + (h - 1) *	subsampling_dy + 1;

	/* set image data */

	if ((value == '2') || (value == '3')) {	/* ASCII */
		for (i = 0; i < w * h; i++) {
			for(compno = 0; compno < numcomps; compno++) {
				unsigned int index = 0;
				fscanf(f, "%u", &index);
				/* compno : 0 = GREY, (0, 1, 2) = (R, G, B) */
				image->comps[compno].data[i] = index;
			}
		}
	} else if ((value == '5') || (value == '6')) {	/* BINARY */
		for (i = 0; i < w * h; i++) {
			for(compno = 0; compno < numcomps; compno++) {
				unsigned char index = 0;
				fread(&index, 1, 1, f);
				/* compno : 0 = GREY, (0, 1, 2) = (R, G, B) */
				image->comps[compno].data[i] = index;
			}
		}
	}

	fclose(f);

	return image;
}