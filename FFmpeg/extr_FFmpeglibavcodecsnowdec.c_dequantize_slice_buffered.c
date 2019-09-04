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
typedef  int /*<<< orphan*/  slice_buffer ;
struct TYPE_6__ {int const qbias; int /*<<< orphan*/  qlog; } ;
struct TYPE_5__ {int width; int stride_line; int buf_x_offset; scalar_t__ buf_y_offset; int /*<<< orphan*/  qlog; } ;
typedef  TYPE_1__ SubBand ;
typedef  TYPE_2__ SnowContext ;
typedef  int IDWTELEM ;

/* Variables and functions */
 int /*<<< orphan*/  LOSSLESS_QLOG ; 
 int const QBIAS_SHIFT ; 
 int QEXPSHIFT ; 
 int QROOT ; 
 int const QSHIFT ; 
 int av_clip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int const* ff_qexp ; 
 int* slice_buffer_get_line (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void dequantize_slice_buffered(SnowContext *s, slice_buffer * sb, SubBand *b, IDWTELEM *src, int stride, int start_y, int end_y){
    const int w= b->width;
    const int qlog= av_clip(s->qlog + b->qlog, 0, QROOT*16);
    const int qmul= ff_qexp[qlog&(QROOT-1)]<<(qlog>>QSHIFT);
    const int qadd= (s->qbias*qmul)>>QBIAS_SHIFT;
    int x,y;

    if(s->qlog == LOSSLESS_QLOG) return;

    for(y=start_y; y<end_y; y++){
//        DWTELEM * line = slice_buffer_get_line_from_address(sb, src + (y * stride));
        IDWTELEM * line = slice_buffer_get_line(sb, (y * b->stride_line) + b->buf_y_offset) + b->buf_x_offset;
        for(x=0; x<w; x++){
            int i= line[x];
            if(i<0){
                line[x]= -((-i*(unsigned)qmul + qadd)>>(QEXPSHIFT)); //FIXME try different bias
            }else if(i>0){
                line[x]=  (( i*(unsigned)qmul + qadd)>>(QEXPSHIFT));
            }
        }
    }
}