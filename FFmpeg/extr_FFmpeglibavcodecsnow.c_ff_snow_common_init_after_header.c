#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x_and_coeff ;
struct TYPE_16__ {scalar_t__ format; int /*<<< orphan*/ * linesize; } ;
struct TYPE_15__ {int width; int height; } ;
struct TYPE_14__ {int width; scalar_t__ pix_fmt; TYPE_3__* priv_data; } ;
struct TYPE_13__ {int nb_planes; int spatial_decomposition_count; TYPE_1__* plane; scalar_t__ spatial_dwt_buffer; scalar_t__ spatial_idwt_buffer; int /*<<< orphan*/  chroma_v_shift; int /*<<< orphan*/  chroma_h_shift; TYPE_6__* avctx; TYPE_7__* mconly_picture; int /*<<< orphan*/  emu_edge_buffer; int /*<<< orphan*/  scratchbuf; } ;
struct TYPE_12__ {int level; int stride; int width; int height; int stride_line; int buf_x_offset; int buf_y_offset; int /*<<< orphan*/  x_coeff; struct TYPE_12__* parent; scalar_t__ buf; scalar_t__ ibuf; } ;
struct TYPE_11__ {int width; int height; TYPE_2__** band; } ;
typedef  TYPE_2__ SubBand ;
typedef  TYPE_3__ SnowContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FF_ALLOCZ_ARRAY_OR_GOTO (TYPE_4__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FF_ALLOC_OR_GOTO (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int HTAPS_MAX ; 
 int MB_SIZE ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_mallocz_array (int,int) ; 
 int /*<<< orphan*/  fail ; 
 int ff_get_buffer (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ ) ; 

int ff_snow_common_init_after_header(AVCodecContext *avctx) {
    SnowContext *s = avctx->priv_data;
    int plane_index, level, orientation;
    int ret, emu_buf_size;

    if(!s->scratchbuf) {
        if ((ret = ff_get_buffer(s->avctx, s->mconly_picture,
                                 AV_GET_BUFFER_FLAG_REF)) < 0)
            return ret;
        FF_ALLOCZ_ARRAY_OR_GOTO(avctx, s->scratchbuf, FFMAX(s->mconly_picture->linesize[0], 2*avctx->width+256), 7*MB_SIZE, fail);
        emu_buf_size = FFMAX(s->mconly_picture->linesize[0], 2*avctx->width+256) * (2 * MB_SIZE + HTAPS_MAX - 1);
        FF_ALLOC_OR_GOTO(avctx, s->emu_edge_buffer, emu_buf_size, fail);
    }

    if(s->mconly_picture->format != avctx->pix_fmt) {
        av_log(avctx, AV_LOG_ERROR, "pixel format changed\n");
        return AVERROR_INVALIDDATA;
    }

    for(plane_index=0; plane_index < s->nb_planes; plane_index++){
        int w= s->avctx->width;
        int h= s->avctx->height;

        if(plane_index){
            w = AV_CEIL_RSHIFT(w, s->chroma_h_shift);
            h = AV_CEIL_RSHIFT(h, s->chroma_v_shift);
        }
        s->plane[plane_index].width = w;
        s->plane[plane_index].height= h;

        for(level=s->spatial_decomposition_count-1; level>=0; level--){
            for(orientation=level ? 1 : 0; orientation<4; orientation++){
                SubBand *b= &s->plane[plane_index].band[level][orientation];

                b->buf= s->spatial_dwt_buffer;
                b->level= level;
                b->stride= s->plane[plane_index].width << (s->spatial_decomposition_count - level);
                b->width = (w + !(orientation&1))>>1;
                b->height= (h + !(orientation>1))>>1;

                b->stride_line = 1 << (s->spatial_decomposition_count - level);
                b->buf_x_offset = 0;
                b->buf_y_offset = 0;

                if(orientation&1){
                    b->buf += (w+1)>>1;
                    b->buf_x_offset = (w+1)>>1;
                }
                if(orientation>1){
                    b->buf += b->stride>>1;
                    b->buf_y_offset = b->stride_line >> 1;
                }
                b->ibuf= s->spatial_idwt_buffer + (b->buf - s->spatial_dwt_buffer);

                if(level)
                    b->parent= &s->plane[plane_index].band[level-1][orientation];
                //FIXME avoid this realloc
                av_freep(&b->x_coeff);
                b->x_coeff=av_mallocz_array(((b->width+1) * b->height+1), sizeof(x_and_coeff));
                if (!b->x_coeff)
                    goto fail;
            }
            w= (w+1)>>1;
            h= (h+1)>>1;
        }
    }

    return 0;
fail:
    return AVERROR(ENOMEM);
}