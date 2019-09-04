#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; int height; } ;
struct TYPE_9__ {int chroma_x_shift; int chroma_y_shift; int pshift; void* blmotion; void* sbsplit; TYPE_3__* plane; TYPE_1__ seq; } ;
struct TYPE_7__ {void* tmp; int /*<<< orphan*/  buf_base; scalar_t__ buf; } ;
struct TYPE_8__ {TYPE_2__ idwt; } ;
typedef  TYPE_4__ DiracContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int CALC_PADDING (int,int) ; 
 int DIVRNDUP (int,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int,int) ; 
 int FFMAX (int,int) ; 
 int MAX_BLOCKSIZE ; 
 int MAX_DWT_LEVELS ; 
 void* av_malloc_array (int,int) ; 
 int /*<<< orphan*/  av_mallocz_array (int,int) ; 

__attribute__((used)) static int alloc_sequence_buffers(DiracContext *s)
{
    int sbwidth  = DIVRNDUP(s->seq.width,  4);
    int sbheight = DIVRNDUP(s->seq.height, 4);
    int i, w, h, top_padding;

    /* todo: think more about this / use or set Plane here */
    for (i = 0; i < 3; i++) {
        int max_xblen = MAX_BLOCKSIZE >> (i ? s->chroma_x_shift : 0);
        int max_yblen = MAX_BLOCKSIZE >> (i ? s->chroma_y_shift : 0);
        w = s->seq.width  >> (i ? s->chroma_x_shift : 0);
        h = s->seq.height >> (i ? s->chroma_y_shift : 0);

        /* we allocate the max we support here since num decompositions can
         * change from frame to frame. Stride is aligned to 16 for SIMD, and
         * 1<<MAX_DWT_LEVELS top padding to avoid if(y>0) in arith decoding
         * MAX_BLOCKSIZE padding for MC: blocks can spill up to half of that
         * on each side */
        top_padding = FFMAX(1<<MAX_DWT_LEVELS, max_yblen/2);
        w = FFALIGN(CALC_PADDING(w, MAX_DWT_LEVELS), 8); /* FIXME: Should this be 16 for SSE??? */
        h = top_padding + CALC_PADDING(h, MAX_DWT_LEVELS) + max_yblen/2;

        s->plane[i].idwt.buf_base = av_mallocz_array((w+max_xblen), h * (2 << s->pshift));
        s->plane[i].idwt.tmp      = av_malloc_array((w+16), 2 << s->pshift);
        s->plane[i].idwt.buf      = s->plane[i].idwt.buf_base + (top_padding*w)*(2 << s->pshift);
        if (!s->plane[i].idwt.buf_base || !s->plane[i].idwt.tmp)
            return AVERROR(ENOMEM);
    }

    /* fixme: allocate using real stride here */
    s->sbsplit  = av_malloc_array(sbwidth, sbheight);
    s->blmotion = av_malloc_array(sbwidth, sbheight * 16 * sizeof(*s->blmotion));

    if (!s->sbsplit || !s->blmotion)
        return AVERROR(ENOMEM);
    return 0;
}