#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* draw_edges ) (scalar_t__,int,int,int,int,int,int) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* dirac_hpel_filter ) (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int) ;} ;
struct TYPE_12__ {TYPE_2__ mpvencdsp; TYPE_1__ diracdsp; int /*<<< orphan*/  mv_precision; } ;
struct TYPE_11__ {int* interpolated; TYPE_3__* avframe; scalar_t__** hpel; scalar_t__** hpel_base; } ;
struct TYPE_10__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_4__ DiracFrame ;
typedef  TYPE_5__ DiracContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int EDGE_BOTTOM ; 
 int EDGE_TOP ; 
 int EDGE_WIDTH ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ av_malloc (int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,int,int,int,int,int,int) ; 

__attribute__((used)) static int interpolate_refplane(DiracContext *s, DiracFrame *ref, int plane, int width, int height)
{
    /* chroma allocates an edge of 8 when subsampled
       which for 4:2:2 means an h edge of 16 and v edge of 8
       just use 8 for everything for the moment */
    int i, edge = EDGE_WIDTH/2;

    ref->hpel[plane][0] = ref->avframe->data[plane];
    s->mpvencdsp.draw_edges(ref->hpel[plane][0], ref->avframe->linesize[plane], width, height, edge, edge, EDGE_TOP | EDGE_BOTTOM); /* EDGE_TOP | EDGE_BOTTOM values just copied to make it build, this needs to be ensured */

    /* no need for hpel if we only have fpel vectors */
    if (!s->mv_precision)
        return 0;

    for (i = 1; i < 4; i++) {
        if (!ref->hpel_base[plane][i])
            ref->hpel_base[plane][i] = av_malloc((height+2*edge) * ref->avframe->linesize[plane] + 32);
        if (!ref->hpel_base[plane][i]) {
            return AVERROR(ENOMEM);
        }
        /* we need to be 16-byte aligned even for chroma */
        ref->hpel[plane][i] = ref->hpel_base[plane][i] + edge*ref->avframe->linesize[plane] + 16;
    }

    if (!ref->interpolated[plane]) {
        s->diracdsp.dirac_hpel_filter(ref->hpel[plane][1], ref->hpel[plane][2],
                                      ref->hpel[plane][3], ref->hpel[plane][0],
                                      ref->avframe->linesize[plane], width, height);
        s->mpvencdsp.draw_edges(ref->hpel[plane][1], ref->avframe->linesize[plane], width, height, edge, edge, EDGE_TOP | EDGE_BOTTOM);
        s->mpvencdsp.draw_edges(ref->hpel[plane][2], ref->avframe->linesize[plane], width, height, edge, edge, EDGE_TOP | EDGE_BOTTOM);
        s->mpvencdsp.draw_edges(ref->hpel[plane][3], ref->avframe->linesize[plane], width, height, edge, edge, EDGE_TOP | EDGE_BOTTOM);
    }
    ref->interpolated[plane] = 1;

    return 0;
}