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
struct TYPE_5__ {int numcomps; TYPE_1__* comps; scalar_t__ y0; scalar_t__ x0; scalar_t__ y1; scalar_t__ x1; } ;
typedef  TYPE_2__ opj_image_t ;
struct TYPE_4__ {scalar_t__ dx; scalar_t__ dy; int prec; int w; int h; int* data; scalar_t__ sgnd; int /*<<< orphan*/  factor; void* y0; void* x0; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int int_ceildiv (scalar_t__,scalar_t__) ; 
 void* int_ceildivpow2 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int imagetopnm(opj_image_t * image, const char *outfile) {
	int w, wr, h, hr, max;
	int i, compno;
	int adjustR, adjustG, adjustB, adjustX;
	FILE *fdest = NULL;
	char S2;
	const char *tmp = outfile;

	while (*tmp) {
		tmp++;
	}
	tmp--;
	tmp--;
	S2 = *tmp;

	if (image->numcomps == 3 && image->comps[0].dx == image->comps[1].dx
		&& image->comps[1].dx == image->comps[2].dx
		&& image->comps[0].dy == image->comps[1].dy
		&& image->comps[1].dy == image->comps[2].dy
		&& image->comps[0].prec == image->comps[1].prec
		&& image->comps[1].prec == image->comps[2].prec
		&& S2 !='g' && S2 !='G') {

		fdest = fopen(outfile, "wb");
		if (!fdest) {
			fprintf(stderr, "ERROR -> failed to open %s for writing\n", outfile);
			return 1;
		}

		w = int_ceildiv(image->x1 - image->x0, image->comps[0].dx);
		wr = image->comps[0].w;
        
		h = int_ceildiv(image->y1 - image->y0, image->comps[0].dy);
		hr = image->comps[0].h;
	    
		max = image->comps[0].prec > 8 ? 255 : (1 << image->comps[0].prec) - 1;
	    
		image->comps[0].x0 = int_ceildivpow2(image->comps[0].x0 - int_ceildiv(image->x0, image->comps[0].dx), image->comps[0].factor);
		image->comps[0].y0 = int_ceildivpow2(image->comps[0].y0 -	int_ceildiv(image->y0, image->comps[0].dy), image->comps[0].factor);

		fprintf(fdest, "P6\n%d %d\n%d\n", wr, hr, max);

		if (image->comps[0].prec > 8) {
			adjustR = image->comps[0].prec - 8;
			printf("PNM CONVERSION: Truncating component 0 from %d bits to 8 bits\n", image->comps[0].prec);
		}
		else 
			adjustR = 0;
		if (image->comps[1].prec > 8) {
			adjustG = image->comps[1].prec - 8;
			printf("PNM CONVERSION: Truncating component 1 from %d bits to 8 bits\n", image->comps[1].prec);
		}
		else 
			adjustG = 0;
		if (image->comps[2].prec > 8) {
			adjustB = image->comps[2].prec - 8;
			printf("PNM CONVERSION: Truncating component 2 from %d bits to 8 bits\n", image->comps[2].prec);
		}
		else 
			adjustB = 0;


		for (i = 0; i < wr * hr; i++) {
			int r, g, b;
			unsigned char rc,gc,bc;
			r = image->comps[0].data[i];
			r += (image->comps[0].sgnd ? 1 << (image->comps[0].prec - 1) : 0);
			rc = (unsigned char) ((r >> adjustR)+((r >> (adjustR-1))%2));

			g = image->comps[1].data[i];
			g += (image->comps[1].sgnd ? 1 << (image->comps[1].prec - 1) : 0);
			gc = (unsigned char) ((g >> adjustG)+((g >> (adjustG-1))%2));
			
			b = image->comps[2].data[i];
			b += (image->comps[2].sgnd ? 1 << (image->comps[2].prec - 1) : 0);
			bc = (unsigned char) ((b >> adjustB)+((b >> (adjustB-1))%2));
			
			fprintf(fdest, "%c%c%c", rc, gc, bc);
		}
		fclose(fdest);

	} else {
		int ncomp=(S2=='g' || S2=='G')?1:image->numcomps;
		if (image->numcomps > ncomp) {
			fprintf(stderr,"WARNING -> [PGM files] Only the first component\n");
			fprintf(stderr,"           is written to the file\n");
		}
		for (compno = 0; compno < ncomp; compno++) {
			char name[256];
			if (ncomp > 1) {
				sprintf(name, "%d.%s", compno, outfile);
			} else {
				sprintf(name, "%s", outfile);
			}
			
			fdest = fopen(name, "wb");
			if (!fdest) {
				fprintf(stderr, "ERROR -> failed to open %s for writing\n", name);
				return 1;
			}
            
			w = int_ceildiv(image->x1 - image->x0, image->comps[compno].dx);
			wr = image->comps[compno].w;
			
			h = int_ceildiv(image->y1 - image->y0, image->comps[compno].dy);
			hr = image->comps[compno].h;
			
			max = image->comps[compno].prec > 8 ? 255 : (1 << image->comps[compno].prec) - 1;
			
			image->comps[compno].x0 = int_ceildivpow2(image->comps[compno].x0 - int_ceildiv(image->x0, image->comps[compno].dx), image->comps[compno].factor);
			image->comps[compno].y0 = int_ceildivpow2(image->comps[compno].y0 - int_ceildiv(image->y0, image->comps[compno].dy), image->comps[compno].factor);
			
			fprintf(fdest, "P5\n%d %d\n%d\n", wr, hr, max);
			
			if (image->comps[compno].prec > 8) {
				adjustX = image->comps[0].prec - 8;
				printf("PNM CONVERSION: Truncating component %d from %d bits to 8 bits\n",compno, image->comps[compno].prec);
			}
			else 
				adjustX = 0;
			
			for (i = 0; i < wr * hr; i++) {
				int l;
				unsigned char lc;
				l = image->comps[compno].data[i];
				l += (image->comps[compno].sgnd ? 1 << (image->comps[compno].prec - 1) : 0);
				lc = (unsigned char) ((l >> adjustX)+((l >> (adjustX-1))%2));
				fprintf(fdest, "%c", lc);
			}
			fclose(fdest);
		}
	}

	return 0;
}