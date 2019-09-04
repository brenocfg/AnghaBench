#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numcomps; void* IPR; void* UnkC; void* C; void* bpc; int /*<<< orphan*/ * comps; void* w; void* h; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_1__ opj_jp2_t ;
typedef  int /*<<< orphan*/  opj_jp2_comps_t ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ init_pos; scalar_t__ length; } ;
typedef  TYPE_2__ opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 scalar_t__ JP2_IHDR ; 
 void* cio_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jp2_read_boxhdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ opj_malloc (int) ; 

__attribute__((used)) static bool jp2_read_ihdr(opj_jp2_t *jp2, opj_cio_t *cio) {
	opj_jp2_box_t box;

	opj_common_ptr cinfo = jp2->cinfo;

	jp2_read_boxhdr(cinfo, cio, &box);
	if (JP2_IHDR != box.type) {
		opj_event_msg(cinfo, EVT_ERROR, "Expected IHDR Marker\n");
		return false;
	}

	jp2->h = cio_read(cio, 4);			/* HEIGHT */
	jp2->w = cio_read(cio, 4);			/* WIDTH */
	jp2->numcomps = cio_read(cio, 2);	/* NC */
	jp2->comps = (opj_jp2_comps_t*) opj_malloc(jp2->numcomps * sizeof(opj_jp2_comps_t));

	jp2->bpc = cio_read(cio, 1);		/* BPC */

	jp2->C = cio_read(cio, 1);			/* C */
	jp2->UnkC = cio_read(cio, 1);		/* UnkC */
	jp2->IPR = cio_read(cio, 1);		/* IPR */

	if (cio_tell(cio) - box.init_pos != box.length) {
		opj_event_msg(cinfo, EVT_ERROR, "Error with IHDR Box\n");
		return false;
	}

	return true;
}