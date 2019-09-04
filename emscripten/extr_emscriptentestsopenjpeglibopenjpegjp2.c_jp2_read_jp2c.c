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
struct TYPE_6__ {scalar_t__ type; int length; } ;
typedef  TYPE_2__ opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 scalar_t__ JP2_JP2C ; 
 int /*<<< orphan*/  cio_skip (int /*<<< orphan*/ *,int) ; 
 unsigned int cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jp2_read_boxhdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static bool jp2_read_jp2c(opj_jp2_t *jp2, opj_cio_t *cio, unsigned int *j2k_codestream_length, unsigned int *j2k_codestream_offset) {
	opj_jp2_box_t box;

	opj_common_ptr cinfo = jp2->cinfo;

	jp2_read_boxhdr(cinfo, cio, &box);
	do {
		if(JP2_JP2C != box.type) {
			cio_skip(cio, box.length - 8);
			jp2_read_boxhdr(cinfo, cio, &box);
		}
	} while(JP2_JP2C != box.type);

	*j2k_codestream_offset = cio_tell(cio);
	*j2k_codestream_length = box.length - 8;

	return true;
}