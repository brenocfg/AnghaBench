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
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_16__ {int /*<<< orphan*/ * pal; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* readAlpPlanar ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* alpToYV12 ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  input_rgb2yuv_table; int /*<<< orphan*/  (* readLumPlanar ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lumToYV12 ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_14__ {TYPE_4__* dst; scalar_t__ alpha; TYPE_2__* src; TYPE_7__* instance; } ;
struct TYPE_13__ {TYPE_3__* plane; } ;
struct TYPE_12__ {int sliceY; int sliceH; int /*<<< orphan*/ ** line; } ;
struct TYPE_11__ {int width; int v_chr_sub_sample; TYPE_1__* plane; } ;
struct TYPE_10__ {int sliceY; int /*<<< orphan*/  const** line; } ;
typedef  TYPE_5__ SwsFilterDescriptor ;
typedef  TYPE_6__ SwsContext ;
typedef  TYPE_7__ ColorContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lum_convert(SwsContext *c, SwsFilterDescriptor *desc, int sliceY, int sliceH)
{
    int srcW = desc->src->width;
    ColorContext * instance = desc->instance;
    uint32_t * pal = instance->pal;
    int i;

    desc->dst->plane[0].sliceY = sliceY;
    desc->dst->plane[0].sliceH = sliceH;
    desc->dst->plane[3].sliceY = sliceY;
    desc->dst->plane[3].sliceH = sliceH;

    for (i = 0; i < sliceH; ++i) {
        int sp0 = sliceY+i - desc->src->plane[0].sliceY;
        int sp1 = ((sliceY+i) >> desc->src->v_chr_sub_sample) - desc->src->plane[1].sliceY;
        const uint8_t * src[4] = { desc->src->plane[0].line[sp0],
                        desc->src->plane[1].line[sp1],
                        desc->src->plane[2].line[sp1],
                        desc->src->plane[3].line[sp0]};
        uint8_t * dst = desc->dst->plane[0].line[i];

        if (c->lumToYV12) {
            c->lumToYV12(dst, src[0], src[1], src[2], srcW, pal);
        } else if (c->readLumPlanar) {
            c->readLumPlanar(dst, src, srcW, c->input_rgb2yuv_table);
        }


        if (desc->alpha) {
            dst = desc->dst->plane[3].line[i];
            if (c->alpToYV12) {
                c->alpToYV12(dst, src[3], src[1], src[2], srcW, pal);
            } else if (c->readAlpPlanar) {
                c->readAlpPlanar(dst, src, srcW, NULL);
            }
        }
    }

    return sliceH;
}