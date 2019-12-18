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
struct TYPE_3__ {int* area_q; int cno; int* bit_size; int* mb; int* next; int /*<<< orphan*/ * save; } ;
typedef  TYPE_1__ EncBlockInfo ;

/* Variables and functions */
 int DV100_QLEVEL_CNO (int /*<<< orphan*/ ) ; 
 int DV100_QLEVEL_QNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dv100_qlevels ; 
 int* dv100_qstep_inv ; 
 int dv100_quantize (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dv_rl2vlc_size (int,int) ; 

__attribute__((used)) static int dv100_actual_quantize(EncBlockInfo *b, int qlevel)
{
    int prev, k, qsinv;

    int qno = DV100_QLEVEL_QNO(dv100_qlevels[qlevel]);
    int cno = DV100_QLEVEL_CNO(dv100_qlevels[qlevel]);

    if (b->area_q[0] == qno && b->cno == cno)
        return b->bit_size[0];

    qsinv = dv100_qstep_inv[qno];

    /* record the new qstep */
    b->area_q[0] = qno;
    b->cno = cno;

    /* reset encoded size (EOB = 4 bits) */
    b->bit_size[0] = 4;

    /* visit nonzero components and quantize */
    prev = 0;
    for (k = 1; k < 64; k++) {
        /* quantize */
        int ac = dv100_quantize(b->save[k], qsinv) >> cno;
        if (ac) {
            if (ac > 255)
                ac = 255;
            b->mb[k] = ac;
            b->bit_size[0] += dv_rl2vlc_size(k - prev - 1, ac);
            b->next[prev] = k;
            prev = k;
        }
    }
    b->next[prev] = k;

    return b->bit_size[0];
}