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
struct TYPE_4__ {int x0; int y0; int x1; int y1; int numcomps; TYPE_2__* comps; } ;
typedef  TYPE_1__ opj_image_t ;
struct TYPE_5__ {int dx; int dy; int prec; int sgnd; } ;
typedef  TYPE_2__ opj_image_comp_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void j2k_dump_image(FILE *fd, opj_image_t * img) {
	int compno;
	fprintf(fd, "image {\n");
	fprintf(fd, "  x0=%d, y0=%d, x1=%d, y1=%d\n", img->x0, img->y0, img->x1, img->y1);
	fprintf(fd, "  numcomps=%d\n", img->numcomps);
	for (compno = 0; compno < img->numcomps; compno++) {
		opj_image_comp_t *comp = &img->comps[compno];
		fprintf(fd, "  comp %d {\n", compno);
		fprintf(fd, "    dx=%d, dy=%d\n", comp->dx, comp->dy);
		fprintf(fd, "    prec=%d\n", comp->prec);
		//fprintf(fd, "    bpp=%d\n", comp->bpp);
		fprintf(fd, "    sgnd=%d\n", comp->sgnd);
		fprintf(fd, "  }\n");
	}
	fprintf(fd, "}\n");
}