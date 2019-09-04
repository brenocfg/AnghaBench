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
struct TYPE_5__ {int maxpasses; scalar_t__ len; scalar_t__ numpasses; scalar_t__ dataindex; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ opj_tcd_seg_t ;
struct TYPE_6__ {TYPE_1__* segs; } ;
typedef  TYPE_2__ opj_tcd_cblk_dec_t ;

/* Variables and functions */
 int J2K_CCP_CBLKSTY_LAZY ; 
 int J2K_CCP_CBLKSTY_TERMALL ; 
 scalar_t__ opj_realloc (TYPE_1__*,int) ; 

__attribute__((used)) static void t2_init_seg(opj_tcd_cblk_dec_t* cblk, int index, int cblksty, int first) {
	opj_tcd_seg_t* seg;
	cblk->segs = (opj_tcd_seg_t*) opj_realloc(cblk->segs, (index + 1) * sizeof(opj_tcd_seg_t));
	seg = &cblk->segs[index];
	seg->data = NULL;
	seg->dataindex = 0;
	seg->numpasses = 0;
	seg->len = 0;
	if (cblksty & J2K_CCP_CBLKSTY_TERMALL) {
		seg->maxpasses = 1;
	}
	else if (cblksty & J2K_CCP_CBLKSTY_LAZY) {
		if (first) {
			seg->maxpasses = 10;
		} else {
			seg->maxpasses = (((seg - 1)->maxpasses == 1) || ((seg - 1)->maxpasses == 10)) ? 2 : 1;
		}
	} else {
		seg->maxpasses = 109;
	}
}