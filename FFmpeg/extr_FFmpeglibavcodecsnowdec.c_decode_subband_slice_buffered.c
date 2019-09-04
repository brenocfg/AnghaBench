#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  slice_buffer ;
struct TYPE_8__ {int qbias; scalar_t__ spatial_idwt_buffer; int /*<<< orphan*/  qlog; } ;
struct TYPE_7__ {int width; scalar_t__ ibuf; int stride_line; int buf_x_offset; TYPE_1__* x_coeff; scalar_t__ buf_y_offset; int /*<<< orphan*/  qlog; } ;
struct TYPE_6__ {int coeff; int x; } ;
typedef  TYPE_2__ SubBand ;
typedef  TYPE_3__ SnowContext ;
typedef  int IDWTELEM ;

/* Variables and functions */
 int /*<<< orphan*/  LOSSLESS_QLOG ; 
 int QBIAS_SHIFT ; 
 int QEXPSHIFT ; 
 int QROOT ; 
 int const QSHIFT ; 
 int av_clip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int const* ff_qexp ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int* slice_buffer_get_line (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline void decode_subband_slice_buffered(SnowContext *s, SubBand *b, slice_buffer * sb, int start_y, int h, int save_state[1]){
    const int w= b->width;
    int y;
    const int qlog= av_clip(s->qlog + b->qlog, 0, QROOT*16);
    int qmul= ff_qexp[qlog&(QROOT-1)]<<(qlog>>QSHIFT);
    int qadd= (s->qbias*qmul)>>QBIAS_SHIFT;
    int new_index = 0;

    if(b->ibuf == s->spatial_idwt_buffer || s->qlog == LOSSLESS_QLOG){
        qadd= 0;
        qmul= 1<<QEXPSHIFT;
    }

    /* If we are on the second or later slice, restore our index. */
    if (start_y != 0)
        new_index = save_state[0];


    for(y=start_y; y<h; y++){
        int x = 0;
        int v;
        IDWTELEM * line = slice_buffer_get_line(sb, y * b->stride_line + b->buf_y_offset) + b->buf_x_offset;
        memset(line, 0, b->width*sizeof(IDWTELEM));
        v = b->x_coeff[new_index].coeff;
        x = b->x_coeff[new_index++].x;
        while(x < w){
            register int t= (int)( (v>>1)*(unsigned)qmul + qadd)>>QEXPSHIFT;
            register int u= -(v&1);
            line[x] = (t^u) - u;

            v = b->x_coeff[new_index].coeff;
            x = b->x_coeff[new_index++].x;
        }
    }

    /* Save our variables for the next slice. */
    save_state[0] = new_index;

    return;
}