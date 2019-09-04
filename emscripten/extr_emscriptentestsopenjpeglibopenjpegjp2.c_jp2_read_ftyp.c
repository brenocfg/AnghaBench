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
struct TYPE_5__ {int numcl; unsigned int* cl; void* minversion; void* brand; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_1__ opj_jp2_t ;
struct TYPE_6__ {scalar_t__ type; int length; int init_pos; } ;
typedef  TYPE_2__ opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 scalar_t__ JP2_FTYP ; 
 void* cio_read (int /*<<< orphan*/ *,int) ; 
 int cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jp2_read_boxhdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ opj_malloc (int) ; 

__attribute__((used)) static bool jp2_read_ftyp(opj_jp2_t *jp2, opj_cio_t *cio) {
	int i;
	opj_jp2_box_t box;

	opj_common_ptr cinfo = jp2->cinfo;

	jp2_read_boxhdr(cinfo, cio, &box);

	if (JP2_FTYP != box.type) {
		opj_event_msg(cinfo, EVT_ERROR, "Expected FTYP Marker\n");
		return false;
	}

	jp2->brand = cio_read(cio, 4);		/* BR */
	jp2->minversion = cio_read(cio, 4);	/* MinV */
	jp2->numcl = (box.length - 16) / 4;
	jp2->cl = (unsigned int *) opj_malloc(jp2->numcl * sizeof(unsigned int));

	for (i = 0; i < (int)jp2->numcl; i++) {
		jp2->cl[i] = cio_read(cio, 4);	/* CLi */
	}

	if (cio_tell(cio) - box.init_pos != box.length) {
		opj_event_msg(cinfo, EVT_ERROR, "Error with FTYP Box\n");
		return false;
	}

	return true;
}