#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; void* type; int /*<<< orphan*/  init_pos; } ;
typedef  TYPE_1__ opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int cio_numbytesleft (int /*<<< orphan*/ *) ; 
 void* cio_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool jp2_read_boxhdr(opj_common_ptr cinfo, opj_cio_t *cio, opj_jp2_box_t *box) {
	box->init_pos = cio_tell(cio);
	box->length = cio_read(cio, 4);
	box->type = cio_read(cio, 4);
	if (box->length == 1) {
		if (cio_read(cio, 4) != 0) {
			opj_event_msg(cinfo, EVT_ERROR, "Cannot handle box sizes higher than 2^32\n");
			return false;
		}
		box->length = cio_read(cio, 4);
		if (box->length == 0) 
			box->length = cio_numbytesleft(cio) + 12;
	}
	else if (box->length == 0) {
		box->length = cio_numbytesleft(cio) + 8;
	}
	
	return true;
}