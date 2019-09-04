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
typedef  int int64_t ;
struct TYPE_9__ {TYPE_3__* h264; TYPE_2__** ref_list; } ;
struct TYPE_8__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_7__ {int poc; TYPE_1__* parent; } ;
struct TYPE_6__ {scalar_t__ long_ref; } ;
typedef  TYPE_4__ H264SliceContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int FFABS (int) ; 
 int av_clip_int8 (int) ; 
 int av_clip_intp2 (int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_scale_factor(H264SliceContext *sl,
                            int poc, int poc1, int i)
{
    int poc0 = sl->ref_list[0][i].poc;
    int64_t pocdiff = poc1 - (int64_t)poc0;
    int td = av_clip_int8(pocdiff);

    if (pocdiff != (int)pocdiff)
        avpriv_request_sample(sl->h264->avctx, "pocdiff overflow\n");

    if (td == 0 || sl->ref_list[0][i].parent->long_ref) {
        return 256;
    } else {
        int64_t pocdiff0 = poc - (int64_t)poc0;
        int tb = av_clip_int8(pocdiff0);
        int tx = (16384 + (FFABS(td) >> 1)) / td;

        if (pocdiff0 != (int)pocdiff0)
            av_log(sl->h264->avctx, AV_LOG_DEBUG, "pocdiff0 overflow\n");

        return av_clip_intp2((tb * tx + 32) >> 6, 10);
    }
}