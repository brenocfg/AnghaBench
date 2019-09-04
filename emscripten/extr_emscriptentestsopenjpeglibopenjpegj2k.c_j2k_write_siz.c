#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* cp; TYPE_3__* image; int /*<<< orphan*/ * cio; } ;
typedef  TYPE_2__ opj_j2k_t ;
struct TYPE_8__ {int x1; int y1; int x0; int y0; int numcomps; TYPE_1__* comps; } ;
typedef  TYPE_3__ opj_image_t ;
struct TYPE_9__ {int rsiz; int tdx; int tdy; int tx0; int ty0; } ;
typedef  TYPE_4__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_6__ {int prec; int sgnd; int dx; int dy; } ;

/* Variables and functions */
 int J2K_MS_SIZ ; 
 int /*<<< orphan*/  cio_seek (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_skip (int /*<<< orphan*/ *,int) ; 
 int cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void j2k_write_siz(opj_j2k_t *j2k) {
	int i;
	int lenp, len;

	opj_cio_t *cio = j2k->cio;
	opj_image_t *image = j2k->image;
	opj_cp_t *cp = j2k->cp;
	
	cio_write(cio, J2K_MS_SIZ, 2);	/* SIZ */
	lenp = cio_tell(cio);
	cio_skip(cio, 2);
	cio_write(cio, cp->rsiz, 2);			/* Rsiz (capabilities) */
	cio_write(cio, image->x1, 4);	/* Xsiz */
	cio_write(cio, image->y1, 4);	/* Ysiz */
	cio_write(cio, image->x0, 4);	/* X0siz */
	cio_write(cio, image->y0, 4);	/* Y0siz */
	cio_write(cio, cp->tdx, 4);		/* XTsiz */
	cio_write(cio, cp->tdy, 4);		/* YTsiz */
	cio_write(cio, cp->tx0, 4);		/* XT0siz */
	cio_write(cio, cp->ty0, 4);		/* YT0siz */
	cio_write(cio, image->numcomps, 2);	/* Csiz */
	for (i = 0; i < image->numcomps; i++) {
		cio_write(cio, image->comps[i].prec - 1 + (image->comps[i].sgnd << 7), 1);	/* Ssiz_i */
		cio_write(cio, image->comps[i].dx, 1);	/* XRsiz_i */
		cio_write(cio, image->comps[i].dy, 1);	/* YRsiz_i */
	}
	len = cio_tell(cio) - lenp;
	cio_seek(cio, lenp);
	cio_write(cio, len, 2);		/* Lsiz */
	cio_seek(cio, lenp + len);
}