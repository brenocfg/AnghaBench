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
struct TYPE_6__ {unsigned int j2k_codestream_offset; unsigned int j2k_codestream_length; TYPE_3__* j2k; } ;
typedef  TYPE_1__ opj_jp2_t ;
struct TYPE_7__ {unsigned int init_pos; int length; } ;
typedef  TYPE_2__ opj_jp2_box_t ;
struct TYPE_8__ {int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_3__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_image_t ;
typedef  int /*<<< orphan*/  opj_codestream_info_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int JP2_JP2C ; 
 int /*<<< orphan*/  cio_seek (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  cio_skip (int /*<<< orphan*/ *,int) ; 
 unsigned int cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  j2k_encode (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int jp2_write_jp2c(opj_jp2_t *jp2, opj_cio_t *cio, opj_image_t *image, opj_codestream_info_t *cstr_info) {
	unsigned int j2k_codestream_offset, j2k_codestream_length;
	opj_jp2_box_t box;

	opj_j2k_t *j2k = jp2->j2k;

	box.init_pos = cio_tell(cio);
	cio_skip(cio, 4);
	cio_write(cio, JP2_JP2C, 4);	/* JP2C */

	/* J2K encoding */
	j2k_codestream_offset = cio_tell(cio);
	if(!j2k_encode(j2k, cio, image, cstr_info)) {
		opj_event_msg(j2k->cinfo, EVT_ERROR, "Failed to encode image\n");
		return 0;
	}
	j2k_codestream_length = cio_tell(cio) - j2k_codestream_offset;

	jp2->j2k_codestream_offset = j2k_codestream_offset;
	jp2->j2k_codestream_length = j2k_codestream_length;

	box.length = 8 + jp2->j2k_codestream_length;
	cio_seek(cio, box.init_pos);
	cio_write(cio, box.length, 4);	/* L */
	cio_seek(cio, box.init_pos + box.length);

	return box.length;
}