#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ overread; int (* get_model_sym ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_14__ {TYPE_1__* c; int /*<<< orphan*/  split_mode; } ;
struct TYPE_13__ {int /*<<< orphan*/  keyframe; } ;
typedef  TYPE_2__ SliceContext ;
typedef  TYPE_3__ ArithCoder ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ MAX_OVERREAD ; 
#define  SPLIT_HOR 130 
#define  SPLIT_NONE 129 
#define  SPLIT_VERT 128 
 int decode_pivot (TYPE_2__*,TYPE_3__*,int) ; 
 int decode_region_inter (TYPE_2__*,TYPE_3__*,int,int,int,int) ; 
 int decode_region_intra (TYPE_2__*,TYPE_3__*,int,int,int,int) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

int ff_mss12_decode_rect(SliceContext *sc, ArithCoder *acoder,
                         int x, int y, int width, int height)
{
    int mode, pivot;
    if (acoder->overread > MAX_OVERREAD)
        return AVERROR_INVALIDDATA;

    mode = acoder->get_model_sym(acoder, &sc->split_mode);

    switch (mode) {
    case SPLIT_VERT:
        if ((pivot = decode_pivot(sc, acoder, height)) < 1)
            return -1;
        if (ff_mss12_decode_rect(sc, acoder, x, y, width, pivot))
            return -1;
        if (ff_mss12_decode_rect(sc, acoder, x, y + pivot, width, height - pivot))
            return -1;
        break;
    case SPLIT_HOR:
        if ((pivot = decode_pivot(sc, acoder, width)) < 1)
            return -1;
        if (ff_mss12_decode_rect(sc, acoder, x, y, pivot, height))
            return -1;
        if (ff_mss12_decode_rect(sc, acoder, x + pivot, y, width - pivot, height))
            return -1;
        break;
    case SPLIT_NONE:
        if (sc->c->keyframe)
            return decode_region_intra(sc, acoder, x, y, width, height);
        else
            return decode_region_inter(sc, acoder, x, y, width, height);
    default:
        return -1;
    }

    return 0;
}