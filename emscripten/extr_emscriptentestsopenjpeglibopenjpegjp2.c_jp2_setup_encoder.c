#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int numcl; unsigned int* cl; int numcomps; int bpc; int C; int meth; int enumcs; scalar_t__ approx; scalar_t__ precedence; TYPE_3__* comps; scalar_t__ IPR; scalar_t__ UnkC; scalar_t__ w; scalar_t__ h; scalar_t__ minversion; void* brand; int /*<<< orphan*/  j2k; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_2__ opj_jp2_t ;
struct TYPE_10__ {int bpcc; } ;
typedef  TYPE_3__ opj_jp2_comps_t ;
struct TYPE_11__ {int numcomps; int color_space; TYPE_1__* comps; scalar_t__ x0; scalar_t__ x1; scalar_t__ y0; scalar_t__ y1; } ;
typedef  TYPE_4__ opj_image_t ;
typedef  int /*<<< orphan*/  opj_cparameters_t ;
struct TYPE_8__ {int prec; int sgnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 void* JP2_JP2 ; 
 int /*<<< orphan*/  j2k_setup_encoder (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ opj_malloc (int) ; 

void jp2_setup_encoder(opj_jp2_t *jp2, opj_cparameters_t *parameters, opj_image_t *image) {
	int i;
	int depth_0, sign;

	if(!jp2 || !parameters || !image)
		return;

	/* setup the J2K codec */
	/* ------------------- */

	/* Check if number of components respects standard */
	if (image->numcomps < 1 || image->numcomps > 16384) {
		opj_event_msg(jp2->cinfo, EVT_ERROR, "Invalid number of components specified while setting up JP2 encoder\n");
		return;
	}

	j2k_setup_encoder(jp2->j2k, parameters, image);

	/* setup the JP2 codec */
	/* ------------------- */
	
	/* Profile box */

	jp2->brand = JP2_JP2;	/* BR */
	jp2->minversion = 0;	/* MinV */
	jp2->numcl = 1;
	jp2->cl = (unsigned int*) opj_malloc(jp2->numcl * sizeof(unsigned int));
	jp2->cl[0] = JP2_JP2;	/* CL0 : JP2 */

	/* Image Header box */

	jp2->numcomps = image->numcomps;	/* NC */
	jp2->comps = (opj_jp2_comps_t*) opj_malloc(jp2->numcomps * sizeof(opj_jp2_comps_t));
	jp2->h = image->y1 - image->y0;		/* HEIGHT */
	jp2->w = image->x1 - image->x0;		/* WIDTH */
	/* BPC */
	depth_0 = image->comps[0].prec - 1;
	sign = image->comps[0].sgnd;
	jp2->bpc = depth_0 + (sign << 7);
	for (i = 1; i < image->numcomps; i++) {
		int depth = image->comps[i].prec - 1;
		sign = image->comps[i].sgnd;
		if (depth_0 != depth)
			jp2->bpc = 255;
	}
	jp2->C = 7;			/* C : Always 7 */
	jp2->UnkC = 0;		/* UnkC, colorspace specified in colr box */
	jp2->IPR = 0;		/* IPR, no intellectual property */
	
	/* BitsPerComponent box */

	for (i = 0; i < image->numcomps; i++) {
		jp2->comps[i].bpcc = image->comps[i].prec - 1 + (image->comps[i].sgnd << 7);
	}

	/* Colour Specification box */

	if ((image->numcomps == 1 || image->numcomps == 3) && (jp2->bpc != 255)) {
		jp2->meth = 1;	/* METH: Enumerated colourspace */
	} else {
		jp2->meth = 2;	/* METH: Restricted ICC profile */
	}
	if (jp2->meth == 1) {
		if (image->color_space == 1)
			jp2->enumcs = 16;	/* sRGB as defined by IEC 61966𣇻 */
		else if (image->color_space == 2)
			jp2->enumcs = 17;	/* greyscale */
		else if (image->color_space == 3)
			jp2->enumcs = 18;	/* YUV */
	} else {
		jp2->enumcs = 0;		/* PROFILE (??) */
	}
	jp2->precedence = 0;	/* PRECEDENCE */
	jp2->approx = 0;		/* APPROX */

}