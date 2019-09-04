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
struct TYPE_3__ {int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_1__ opj_j2k_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_WARNING ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void j2k_read_unk(opj_j2k_t *j2k) {
	opj_event_msg(j2k->cinfo, EVT_WARNING, "Unknown marker\n");

#ifdef USE_JPWL
	if (j2k->cp->correct) {
		int m = 0, id, i;
		int min_id = 0, min_dist = 17, cur_dist = 0, tmp_id;
		cio_seek(j2k->cio, cio_tell(j2k->cio) - 2);
		id = cio_read(j2k->cio, 2);
		opj_event_msg(j2k->cinfo, EVT_ERROR,
			"JPWL: really don't know this marker %x\n",
			id);
		if (!JPWL_ASSUME) {
			opj_event_msg(j2k->cinfo, EVT_ERROR,
				"- possible synch loss due to uncorrectable codestream errors => giving up\n");
			return;
		}
		/* OK, activate this at your own risk!!! */
		/* we look for the marker at the minimum hamming distance from this */
		while (j2k_dec_mstab[m].id) {
			
			/* 1's where they differ */
			tmp_id = j2k_dec_mstab[m].id ^ id;

			/* compute the hamming distance between our id and the current */
			cur_dist = 0;
			for (i = 0; i < 16; i++) {
				if ((tmp_id >> i) & 0x0001) {
					cur_dist++;
				}
			}

			/* if current distance is smaller, set the minimum */
			if (cur_dist < min_dist) {
				min_dist = cur_dist;
				min_id = j2k_dec_mstab[m].id;
			}
			
			/* jump to the next marker */
			m++;
		}

		/* do we substitute the marker? */
		if (min_dist < JPWL_MAXIMUM_HAMMING) {
			opj_event_msg(j2k->cinfo, EVT_ERROR,
				"- marker %x is at distance %d from the read %x\n",
				min_id, min_dist, id);
			opj_event_msg(j2k->cinfo, EVT_ERROR,
				"- trying to substitute in place and crossing fingers!\n");
			cio_seek(j2k->cio, cio_tell(j2k->cio) - 2);
			cio_write(j2k->cio, min_id, 2);

			/* rewind */
			cio_seek(j2k->cio, cio_tell(j2k->cio) - 2);

		}

	};
#endif /* USE_JPWL */

}