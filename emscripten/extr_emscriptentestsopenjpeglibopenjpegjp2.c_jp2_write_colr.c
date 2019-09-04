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
struct TYPE_4__ {int meth; int precedence; int approx; int enumcs; } ;
typedef  TYPE_1__ opj_jp2_t ;
struct TYPE_5__ {void* init_pos; int length; } ;
typedef  TYPE_2__ opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int JP2_COLR ; 
 int /*<<< orphan*/  cio_seek (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  cio_skip (int /*<<< orphan*/ *,int) ; 
 void* cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void jp2_write_colr(opj_jp2_t *jp2, opj_cio_t *cio) {
	opj_jp2_box_t box;

	box.init_pos = cio_tell(cio);
	cio_skip(cio, 4);
	cio_write(cio, JP2_COLR, 4);		/* COLR */

	cio_write(cio, jp2->meth, 1);		/* METH */
	cio_write(cio, jp2->precedence, 1);	/* PRECEDENCE */
	cio_write(cio, jp2->approx, 1);		/* APPROX */

	if (jp2->meth == 1) {
		cio_write(cio, jp2->enumcs, 4);	/* EnumCS */
	} else {
		cio_write(cio, 0, 1);			/* PROFILE (??) */
	}

	box.length = cio_tell(cio) - box.init_pos;
	cio_seek(cio, box.init_pos);
	cio_write(cio, box.length, 4);	/* L */
	cio_seek(cio, box.init_pos + box.length);
}