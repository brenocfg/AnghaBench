#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int numcomps; TYPE_1__* comps; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_2__ opj_jp2_t ;
struct TYPE_8__ {scalar_t__ type; scalar_t__ init_pos; scalar_t__ length; } ;
typedef  TYPE_3__ opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_6__ {int /*<<< orphan*/  bpcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 scalar_t__ JP2_BPCC ; 
 int /*<<< orphan*/  cio_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jp2_read_boxhdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool jp2_read_bpcc(opj_jp2_t *jp2, opj_cio_t *cio) {
	unsigned int i;
	opj_jp2_box_t box;

	opj_common_ptr cinfo = jp2->cinfo;

	jp2_read_boxhdr(cinfo, cio, &box);
	if (JP2_BPCC != box.type) {
		opj_event_msg(cinfo, EVT_ERROR, "Expected BPCC Marker\n");
		return false;
	}

	for (i = 0; i < jp2->numcomps; i++) {
		jp2->comps[i].bpcc = cio_read(cio, 1);
	}

	if (cio_tell(cio) - box.init_pos != box.length) {
		opj_event_msg(cinfo, EVT_ERROR, "Error with BPCC Box\n");
		return false;
	}

	return true;
}