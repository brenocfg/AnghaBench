#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int state; TYPE_1__* cp; int /*<<< orphan*/ * image; int /*<<< orphan*/ * cstr_info; int /*<<< orphan*/ * cio; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_2__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_image_t ;
struct TYPE_10__ {int states; scalar_t__ id; int /*<<< orphan*/  (* handler ) (TYPE_2__*) ;} ;
typedef  TYPE_3__ opj_dec_mstabent_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
typedef  int /*<<< orphan*/  opj_codestream_info_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_8__ {scalar_t__ limit_decoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  EVT_INFO ; 
 int /*<<< orphan*/  EVT_WARNING ; 
 scalar_t__ J2K_MS_SOT ; 
 int J2K_STATE_ERR ; 
 int J2K_STATE_MHSOC ; 
 int J2K_STATE_MT ; 
 int J2K_STATE_NEOC ; 
 scalar_t__ LIMIT_TO_MAIN_HEADER ; 
 int cio_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ cio_tell (int /*<<< orphan*/ *) ; 
 TYPE_3__* j2k_dec_mstab_lookup (int) ; 
 int /*<<< orphan*/  j2k_read_eoc (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * opj_image_create0 () ; 
 int /*<<< orphan*/  opj_image_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

opj_image_t* j2k_decode(opj_j2k_t *j2k, opj_cio_t *cio, opj_codestream_info_t *cstr_info) {
	opj_image_t *image = NULL;

	opj_common_ptr cinfo = j2k->cinfo;	

	j2k->cio = cio;
	j2k->cstr_info = cstr_info;
	if (cstr_info)
		memset(cstr_info, 0, sizeof(opj_codestream_info_t));

	/* create an empty image */
	image = opj_image_create0();
	j2k->image = image;

	j2k->state = J2K_STATE_MHSOC;

	for (;;) {
		opj_dec_mstabent_t *e;
		int id = cio_read(cio, 2);

#ifdef USE_JPWL
		/* we try to honor JPWL correction power */
		if (j2k->cp->correct) {

			int orig_pos = cio_tell(cio);
			bool status;

			/* call the corrector */
			status = jpwl_correct(j2k);

			/* go back to where you were */
			cio_seek(cio, orig_pos - 2);

			/* re-read the marker */
			id = cio_read(cio, 2);

			/* check whether it begins with ff */
			if (id >> 8 != 0xff) {
				opj_event_msg(cinfo, EVT_ERROR,
					"JPWL: possible bad marker %x at %d\n",
					id, cio_tell(cio) - 2);
				if (!JPWL_ASSUME) {
					opj_image_destroy(image);
					opj_event_msg(cinfo, EVT_ERROR, "JPWL: giving up\n");
					return 0;
				}
				/* we try to correct */
				id = id | 0xff00;
				cio_seek(cio, cio_tell(cio) - 2);
				cio_write(cio, id, 2);
				opj_event_msg(cinfo, EVT_WARNING, "- trying to adjust this\n"
					"- setting marker to %x\n",
					id);
			}

		}
#endif /* USE_JPWL */

		if (id >> 8 != 0xff) {
			opj_image_destroy(image);
			opj_event_msg(cinfo, EVT_ERROR, "%.8x: expected a marker instead of %x\n", cio_tell(cio) - 2, id);
			return 0;
		}
		e = j2k_dec_mstab_lookup(id);
		// Check if the marker is known
		if (!(j2k->state & e->states)) {
			opj_image_destroy(image);
			opj_event_msg(cinfo, EVT_ERROR, "%.8x: unexpected marker %x\n", cio_tell(cio) - 2, id);
			return 0;
		}
		// Check if the decoding is limited to the main header
		if (e->id == J2K_MS_SOT && j2k->cp->limit_decoding == LIMIT_TO_MAIN_HEADER) {
			opj_event_msg(cinfo, EVT_INFO, "Main Header decoded.\n");
			return image;
		}		

		if (e->handler) {
			(*e->handler)(j2k);
		}
		if (j2k->state & J2K_STATE_ERR) 
			return NULL;	

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