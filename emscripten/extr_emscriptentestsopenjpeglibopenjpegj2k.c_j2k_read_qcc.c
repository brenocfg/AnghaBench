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
struct TYPE_6__ {int /*<<< orphan*/ * cio; TYPE_1__* image; } ;
typedef  TYPE_2__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_5__ {int numcomps; } ;

/* Variables and functions */
 int cio_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  j2k_read_qcx (TYPE_2__*,int,int) ; 

__attribute__((used)) static void j2k_read_qcc(opj_j2k_t *j2k) {
	int len, compno;
	int numcomp = j2k->image->numcomps;
	opj_cio_t *cio = j2k->cio;
	
	len = cio_read(cio, 2);	/* Lqcc */
	compno = cio_read(cio, numcomp <= 256 ? 1 : 2);	/* Cqcc */

#ifdef USE_JPWL
	if (j2k->cp->correct) {

		static int backup_compno = 0;

		/* compno is negative or larger than the number of components!!! */
		if ((compno < 0) || (compno >= numcomp)) {
			opj_event_msg(j2k->cinfo, EVT_ERROR,
				"JPWL: bad component number in QCC (%d out of a maximum of %d)\n",
				compno, numcomp);
			if (!JPWL_ASSUME) {
				opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
				return;
			}
			/* we try to correct */
			compno = backup_compno % numcomp;
			opj_event_msg(j2k->cinfo, EVT_WARNING, "- trying to adjust this\n"
				"- setting component number to %d\n",
				compno);
		}

		/* keep your private count of tiles */
		backup_compno++;
	};
#endif /* USE_JPWL */

	j2k_read_qcx(j2k, compno, len - 2 - (numcomp <= 256 ? 1 : 2));
}