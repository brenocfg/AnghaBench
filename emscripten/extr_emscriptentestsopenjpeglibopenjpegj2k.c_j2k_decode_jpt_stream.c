#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int Class_Id; unsigned int Msg_length; } ;
typedef  TYPE_1__ opj_jpt_msg_header_t ;
struct TYPE_11__ {int state; int /*<<< orphan*/ * image; int /*<<< orphan*/ * cio; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_2__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_image_t ;
struct TYPE_12__ {int states; int /*<<< orphan*/  (* handler ) (TYPE_2__*) ;} ;
typedef  TYPE_3__ opj_dec_mstabent_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
typedef  int /*<<< orphan*/  opj_codestream_info_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  EVT_WARNING ; 
 int J2K_STATE_MHSOC ; 
 int J2K_STATE_MT ; 
 int J2K_STATE_NEOC ; 
 int /*<<< orphan*/  cio_numbytesleft (int /*<<< orphan*/ *) ; 
 int cio_read (int /*<<< orphan*/ *,int) ; 
 int cio_tell (int /*<<< orphan*/ *) ; 
 TYPE_3__* j2k_dec_mstab_lookup (int) ; 
 int /*<<< orphan*/  j2k_read_eoc (TYPE_2__*) ; 
 int /*<<< orphan*/  jpt_init_msg_header (TYPE_1__*) ; 
 int /*<<< orphan*/  jpt_read_msg_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * opj_image_create0 () ; 
 int /*<<< orphan*/  opj_image_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

opj_image_t* j2k_decode_jpt_stream(opj_j2k_t *j2k, opj_cio_t *cio,  opj_codestream_info_t *cstr_info) {
	opj_image_t *image = NULL;
	opj_jpt_msg_header_t header;
	int position;

	opj_common_ptr cinfo = j2k->cinfo;
	
	j2k->cio = cio;

	/* create an empty image */
	image = opj_image_create0();
	j2k->image = image;

	j2k->state = J2K_STATE_MHSOC;
	
	/* Initialize the header */
	jpt_init_msg_header(&header);
	/* Read the first header of the message */
	jpt_read_msg_header(cinfo, cio, &header);
	
	position = cio_tell(cio);
	if (header.Class_Id != 6) {	/* 6 : Main header data-bin message */
		opj_image_destroy(image);
		opj_event_msg(cinfo, EVT_ERROR, "[JPT-stream] : Expecting Main header first [class_Id %d] !\n", header.Class_Id);
		return 0;
	}
	
	for (;;) {
		opj_dec_mstabent_t *e = NULL;
		int id;
		
		if (!cio_numbytesleft(cio)) {
			j2k_read_eoc(j2k);
			return image;
		}
		/* data-bin read -> need to read a new header */
		if ((unsigned int) (cio_tell(cio) - position) == header.Msg_length) {
			jpt_read_msg_header(cinfo, cio, &header);
			position = cio_tell(cio);
			if (header.Class_Id != 4) {	/* 4 : Tile data-bin message */
				opj_image_destroy(image);
				opj_event_msg(cinfo, EVT_ERROR, "[JPT-stream] : Expecting Tile info !\n");
				return 0;
			}
		}
		
		id = cio_read(cio, 2);
		if (id >> 8 != 0xff) {
			opj_image_destroy(image);
			opj_event_msg(cinfo, EVT_ERROR, "%.8x: expected a marker instead of %x\n", cio_tell(cio) - 2, id);
			return 0;
		}
		e = j2k_dec_mstab_lookup(id);
		if (!(j2k->state & e->states)) {
			opj_image_destroy(image);
			opj_event_msg(cinfo, EVT_ERROR, "%.8x: unexpected marker %x\n", cio_tell(cio) - 2, id);
			return 0;
		}
		if (e->handler) {
			(*e->handler)(j2k);
		}
		if (j2k->state == J2K_STATE_MT) {
			break;
		}
		if (j2k->state == J2K_STATE_NEOC) {
			break;
		}
	}
	if (j2k->state == J2K_STATE_NEOC) {
		j2k_read_eoc(j2k);
	}
	
	if (j2k->state != J2K_STATE_MT) {
		opj_event_msg(cinfo, EVT_WARNING, "Incomplete bitstream\n");
	}

	return image;
}