#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t int8_t ;
struct TYPE_7__ {size_t qscale; int linesize; int uvlinesize; int /*<<< orphan*/ ** dest; } ;
struct TYPE_6__ {int* avail_cache; int intra_types_stride; int /*<<< orphan*/  chroma_vlc; int /*<<< orphan*/  luma_vlc; TYPE_2__ s; } ;
typedef  TYPE_1__ RV34DecContext ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  fill_rectangle (int*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int* ittrans ; 
 size_t** rv34_chroma_quant ; 
 int /*<<< orphan*/  rv34_pred_4x4_block (TYPE_1__*,int /*<<< orphan*/ *,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  rv34_process_block (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int) ; 
 int* rv34_qscale_tab ; 

__attribute__((used)) static void rv34_output_intra(RV34DecContext *r, int8_t *intra_types, int cbp)
{
    MpegEncContext *s   = &r->s;
    uint8_t        *dst = s->dest[0];
    int      avail[6*8] = {0};
    int i, j, k;
    int idx, q_ac, q_dc;

    // Set neighbour information.
    if(r->avail_cache[1])
        avail[0] = 1;
    if(r->avail_cache[2])
        avail[1] = avail[2] = 1;
    if(r->avail_cache[3])
        avail[3] = avail[4] = 1;
    if(r->avail_cache[4])
        avail[5] = 1;
    if(r->avail_cache[5])
        avail[8] = avail[16] = 1;
    if(r->avail_cache[9])
        avail[24] = avail[32] = 1;

    q_ac = rv34_qscale_tab[s->qscale];
    for(j = 0; j < 4; j++){
        idx = 9 + j*8;
        for(i = 0; i < 4; i++, cbp >>= 1, dst += 4, idx++){
            rv34_pred_4x4_block(r, dst, s->linesize, ittrans[intra_types[i]], avail[idx-8], avail[idx-1], avail[idx+7], avail[idx-7]);
            avail[idx] = 1;
            if(!(cbp & 1)) continue;

            rv34_process_block(r, dst, s->linesize,
                               r->luma_vlc, 0, q_ac, q_ac);
        }
        dst += s->linesize * 4 - 4*4;
        intra_types += r->intra_types_stride;
    }

    intra_types -= r->intra_types_stride * 4;

    q_dc = rv34_qscale_tab[rv34_chroma_quant[1][s->qscale]];
    q_ac = rv34_qscale_tab[rv34_chroma_quant[0][s->qscale]];

    for(k = 0; k < 2; k++){
        dst = s->dest[1+k];
        fill_rectangle(r->avail_cache + 6, 2, 2, 4, 0, 4);

        for(j = 0; j < 2; j++){
            int* acache = r->avail_cache + 6 + j*4;
            for(i = 0; i < 2; i++, cbp >>= 1, acache++){
                int itype = ittrans[intra_types[i*2+j*2*r->intra_types_stride]];
                rv34_pred_4x4_block(r, dst+4*i, s->uvlinesize, itype, acache[-4], acache[-1], !i && !j, acache[-3]);
                acache[0] = 1;

                if(!(cbp&1)) continue;

                rv34_process_block(r, dst + 4*i, s->uvlinesize,
                                   r->chroma_vlc, 1, q_dc, q_ac);
            }

            dst += 4*s->uvlinesize;
        }
    }
}