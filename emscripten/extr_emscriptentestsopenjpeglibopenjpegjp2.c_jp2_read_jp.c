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
struct TYPE_5__ {int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_1__ opj_jp2_t ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ init_pos; scalar_t__ length; } ;
typedef  TYPE_2__ opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 scalar_t__ JP2_JP ; 
 int cio_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jp2_read_boxhdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool jp2_read_jp(opj_jp2_t *jp2, opj_cio_t *cio) {
	opj_jp2_box_t box;

	opj_common_ptr cinfo = jp2->cinfo;

	jp2_read_boxhdr(cinfo, cio, &box);
	if (JP2_JP != box.type) {
		opj_event_msg(cinfo, EVT_ERROR, "Expected JP Marker\n");
		return false;
	}
	if (0x0d0a870a != cio_read(cio, 4)) {
		opj_event_msg(cinfo, EVT_ERROR, "Error with JP Marker\n");
		return false;
	}
	if (cio_tell(cio) - box.init_pos != box.length) {
		opj_event_msg(cinfo, EVT_ERROR, "Error with JP Box size\n");
		return false;
	}

	return true;
}