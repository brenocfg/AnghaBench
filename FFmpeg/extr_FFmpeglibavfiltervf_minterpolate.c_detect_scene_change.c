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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_9__ {int width; int height; } ;
struct TYPE_8__ {scalar_t__ scd_method; double prev_mafd; double scd_threshold; int /*<<< orphan*/  (* sad ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,scalar_t__*) ;TYPE_2__* frames; TYPE_4__ me_ctx; } ;
struct TYPE_7__ {TYPE_1__* avf; } ;
struct TYPE_6__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_3__ MIContext ;
typedef  TYPE_4__ AVMotionEstContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (double,double) ; 
 scalar_t__ SCD_METHOD_FDIFF ; 
 double av_clipf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  emms_c () ; 
 double fabs (double) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 

__attribute__((used)) static int detect_scene_change(MIContext *mi_ctx)
{
    AVMotionEstContext *me_ctx = &mi_ctx->me_ctx;
    uint8_t *p1 = mi_ctx->frames[1].avf->data[0];
    ptrdiff_t linesize1 = mi_ctx->frames[1].avf->linesize[0];
    uint8_t *p2 = mi_ctx->frames[2].avf->data[0];
    ptrdiff_t linesize2 = mi_ctx->frames[2].avf->linesize[0];

    if (mi_ctx->scd_method == SCD_METHOD_FDIFF) {
        double ret = 0, mafd, diff;
        uint64_t sad;
        mi_ctx->sad(p1, linesize1, p2, linesize2, me_ctx->width, me_ctx->height, &sad);
        emms_c();
        mafd = (double) sad / (me_ctx->height * me_ctx->width * 3);
        diff = fabs(mafd - mi_ctx->prev_mafd);
        ret  = av_clipf(FFMIN(mafd, diff), 0, 100.0);
        mi_ctx->prev_mafd = mafd;

        return ret >= mi_ctx->scd_threshold;
    }

    return 0;
}