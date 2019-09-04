#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int numpasses; int /*<<< orphan*/  len; scalar_t__ dataindex; scalar_t__* data; } ;
typedef  TYPE_1__ opj_tcd_seg_t ;
struct TYPE_15__ {int numbps; int numsegs; TYPE_1__* segs; scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
typedef  TYPE_2__ opj_tcd_cblk_dec_t ;
struct TYPE_16__ {int /*<<< orphan*/ * mqc; int /*<<< orphan*/ * raw; } ;
typedef  TYPE_3__ opj_t1_t ;
typedef  int /*<<< orphan*/  opj_raw_t ;
typedef  int /*<<< orphan*/  opj_mqc_t ;

/* Variables and functions */
 int J2K_CCP_CBLKSTY_LAZY ; 
 int J2K_CCP_CBLKSTY_RESET ; 
 int J2K_CCP_CBLKSTY_VSC ; 
 int /*<<< orphan*/  T1_CTXNO_AGG ; 
 int /*<<< orphan*/  T1_CTXNO_UNI ; 
 int /*<<< orphan*/  T1_CTXNO_ZC ; 
 char T1_TYPE_MQ ; 
 char T1_TYPE_RAW ; 
 int /*<<< orphan*/  allocate_buffers (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mqc_init_dec (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mqc_resetstates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mqc_setstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_init_dec (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_dec_clnpass (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  t1_dec_refpass_mqc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  t1_dec_refpass_mqc_vsc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  t1_dec_refpass_raw (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  t1_dec_sigpass_mqc (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  t1_dec_sigpass_mqc_vsc (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  t1_dec_sigpass_raw (TYPE_3__*,int,int,int) ; 

__attribute__((used)) static void t1_decode_cblk(
		opj_t1_t *t1,
		opj_tcd_cblk_dec_t* cblk,
		int orient,
		int roishift,
		int cblksty)
{
	opj_raw_t *raw = t1->raw;	/* RAW component */
	opj_mqc_t *mqc = t1->mqc;	/* MQC component */

	int bpno, passtype;
	int segno, passno;
	char type = T1_TYPE_MQ; /* BYPASS mode */

	if(!allocate_buffers(
				t1,
				cblk->x1 - cblk->x0,
				cblk->y1 - cblk->y0))
	{
		return;
	}

	bpno = roishift + cblk->numbps - 1;
	passtype = 2;
	
	mqc_resetstates(mqc);
	mqc_setstate(mqc, T1_CTXNO_UNI, 0, 46);
	mqc_setstate(mqc, T1_CTXNO_AGG, 0, 3);
	mqc_setstate(mqc, T1_CTXNO_ZC, 0, 4);
	
	for (segno = 0; segno < cblk->numsegs; ++segno) {
		opj_tcd_seg_t *seg = &cblk->segs[segno];
		
		/* BYPASS mode */
		type = ((bpno <= (cblk->numbps - 1) - 4) && (passtype < 2) && (cblksty & J2K_CCP_CBLKSTY_LAZY)) ? T1_TYPE_RAW : T1_TYPE_MQ;
		/* FIXME: slviewer gets here with a null pointer. Why? Partially downloaded and/or corrupt textures? */
		if(seg->data == NULL){
			continue;
		}
		if (type == T1_TYPE_RAW) {
			raw_init_dec(raw, (*seg->data) + seg->dataindex, seg->len);
		} else {
			mqc_init_dec(mqc, (*seg->data) + seg->dataindex, seg->len);
		}
		
		for (passno = 0; passno < seg->numpasses; ++passno) {
			switch (passtype) {
				case 0:
					if (type == T1_TYPE_RAW) {
						t1_dec_sigpass_raw(t1, bpno+1, orient, cblksty);
					} else {
						if (cblksty & J2K_CCP_CBLKSTY_VSC) {
							t1_dec_sigpass_mqc_vsc(t1, bpno+1, orient);
						} else {
							t1_dec_sigpass_mqc(t1, bpno+1, orient);
						}
					}
					break;
				case 1:
					if (type == T1_TYPE_RAW) {
						t1_dec_refpass_raw(t1, bpno+1, cblksty);
					} else {
						if (cblksty & J2K_CCP_CBLKSTY_VSC) {
							t1_dec_refpass_mqc_vsc(t1, bpno+1);
						} else {
							t1_dec_refpass_mqc(t1, bpno+1);
						}
					}
					break;
				case 2:
					t1_dec_clnpass(t1, bpno+1, orient, cblksty);
					break;
			}
			
			if ((cblksty & J2K_CCP_CBLKSTY_RESET) && type == T1_TYPE_MQ) {
				mqc_resetstates(mqc);
				mqc_setstate(mqc, T1_CTXNO_UNI, 0, 46);				
				mqc_setstate(mqc, T1_CTXNO_AGG, 0, 3);
				mqc_setstate(mqc, T1_CTXNO_ZC, 0, 4);
			}
			if (++passtype == 3) {
				passtype = 0;
				bpno--;
			}
		}
	}
}