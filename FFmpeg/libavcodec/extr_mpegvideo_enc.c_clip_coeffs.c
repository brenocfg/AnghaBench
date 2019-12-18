#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_7__ {scalar_t__ mb_decision; } ;
struct TYPE_5__ {int* permutated; } ;
struct TYPE_6__ {int max_qcoeff; int min_qcoeff; TYPE_4__* avctx; TYPE_1__ intra_scantable; scalar_t__ mb_intra; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 scalar_t__ FF_MB_DECISION_SIMPLE ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int const,int const) ; 

__attribute__((used)) static inline void clip_coeffs(MpegEncContext *s, int16_t *block,
                               int last_index)
{
    int i;
    const int maxlevel = s->max_qcoeff;
    const int minlevel = s->min_qcoeff;
    int overflow = 0;

    if (s->mb_intra) {
        i = 1; // skip clipping of intra dc
    } else
        i = 0;

    for (; i <= last_index; i++) {
        const int j = s->intra_scantable.permutated[i];
        int level = block[j];

        if (level > maxlevel) {
            level = maxlevel;
            overflow++;
        } else if (level < minlevel) {
            level = minlevel;
            overflow++;
        }

        block[j] = level;
    }

    if (overflow && s->avctx->mb_decision == FF_MB_DECISION_SIMPLE)
        av_log(s->avctx, AV_LOG_INFO,
               "warning, clipping %d dct coefficients to %d..%d\n",
               overflow, minlevel, maxlevel);
}