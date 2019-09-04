#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* tccps; } ;
typedef  TYPE_3__ opj_tcp_t ;
struct TYPE_10__ {scalar_t__ state; size_t curtileno; TYPE_1__* image; int /*<<< orphan*/ * cio; TYPE_3__* default_tcp; TYPE_5__* cp; } ;
typedef  TYPE_4__ opj_j2k_t ;
struct TYPE_11__ {TYPE_3__* tcps; } ;
typedef  TYPE_5__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_8__ {void* roishift; } ;
struct TYPE_7__ {int numcomps; } ;

/* Variables and functions */
 scalar_t__ J2K_STATE_TPH ; 
 void* cio_read (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void j2k_read_rgn(opj_j2k_t *j2k) {
	int len, compno, roisty;

	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = j2k->state == J2K_STATE_TPH ? &cp->tcps[j2k->curtileno] : j2k->default_tcp;
	opj_cio_t *cio = j2k->cio;
	int numcomps = j2k->image->numcomps;

	len = cio_read(cio, 2);										/* Lrgn */
	compno = cio_read(cio, numcomps <= 256 ? 1 : 2);			/* Crgn */
	roisty = cio_read(cio, 1);									/* Srgn */

#ifdef USE_JPWL
	if (j2k->cp->correct) {
		/* totlen is negative or larger than the bytes left!!! */
		if (compno >= numcomps) {
			opj_event_msg(j2k->cinfo, EVT_ERROR,
				"JPWL: bad component number in RGN (%d when there are only %d)\n",
				compno, numcomps);
			if (!JPWL_ASSUME || JPWL_ASSUME) {
				opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
				return;
			}
		}
	};
#endif /* USE_JPWL */

	tcp->tccps[compno].roishift = cio_read(cio, 1);				/* SPrgn */
}