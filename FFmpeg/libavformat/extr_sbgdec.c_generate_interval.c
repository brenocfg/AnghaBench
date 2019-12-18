#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ws_intervals {int dummy; } ;
struct TYPE_2__ {int l; int r; } ;
struct sbg_script_synth {scalar_t__ vol; int type; int beat; TYPE_1__ ref; int /*<<< orphan*/  carrier; } ;
struct sbg_script {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
#define  SBG_TYPE_BELL 133 
#define  SBG_TYPE_MIX 132 
#define  SBG_TYPE_NOISE 131 
#define  SBG_TYPE_NONE 130 
#define  SBG_TYPE_SINE 129 
#define  SBG_TYPE_SPIN 128 
 int /*<<< orphan*/  WS_NOISE ; 
 int /*<<< orphan*/  WS_SINE ; 
 int add_bell (struct ws_intervals*,struct sbg_script*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int add_interval (struct ws_intervals*,int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int generate_interval(void *log, struct sbg_script *s,
                             struct ws_intervals *inter,
                             int64_t ts1, int64_t ts2,
                             struct sbg_script_synth *s1,
                             struct sbg_script_synth *s2,
                             int transition)
{
    int r;

    if (ts2 <= ts1 || (s1->vol == 0 && s2->vol == 0))
        return 0;
    switch (s1->type) {
        case SBG_TYPE_NONE:
            break;
        case SBG_TYPE_SINE:
            if (s1->beat == 0 && s2->beat == 0) {
                r = add_interval(inter, WS_SINE, 3, s1->ref.l,
                                 ts1, s1->carrier, s1->vol,
                                 ts2, s2->carrier, s2->vol);
                if (r < 0)
                    return r;
                s2->ref.l = s2->ref.r = r;
            } else {
                r = add_interval(inter, WS_SINE, 1, s1->ref.l,
                                 ts1, s1->carrier + s1->beat / 2, s1->vol,
                                 ts2, s2->carrier + s2->beat / 2, s2->vol);
                if (r < 0)
                    return r;
                s2->ref.l = r;
                r = add_interval(inter, WS_SINE, 2, s1->ref.r,
                                 ts1, s1->carrier - s1->beat / 2, s1->vol,
                                 ts2, s2->carrier - s2->beat / 2, s2->vol);
                if (r < 0)
                    return r;
                s2->ref.r = r;
            }
            break;

        case SBG_TYPE_BELL:
            if (transition == 2) {
                r = add_bell(inter, s, ts1, ts2, s1->carrier, s2->vol);
                if (r < 0)
                    return r;
            }
            break;

        case SBG_TYPE_SPIN:
            av_log(log, AV_LOG_WARNING, "Spinning noise not implemented, "
                                        "using pink noise instead.\n");
            /* fall through */
        case SBG_TYPE_NOISE:
            /* SBaGen's pink noise generator uses:
               - 1 band of white noise, mean square: 1/3;
               - 9 bands of subsampled white noise with linear
                 interpolation, mean square: 2/3 each;
               with 1/10 weight each: the total mean square is 7/300.
               Our pink noise generator uses 8 bands of white noise with
               rectangular subsampling: the total mean square is 1/24.
               Therefore, to match SBaGen's volume, we must multiply vol by
               sqrt((7/300) / (1/24)) = sqrt(14/25) =~ 0.748
             */
            r = add_interval(inter, WS_NOISE, 3, s1->ref.l,
                             ts1, 0, s1->vol - s1->vol / 4,
                             ts2, 0, s2->vol - s2->vol / 4);
            if (r < 0)
                return r;
            s2->ref.l = s2->ref.r = r;
            break;

        case SBG_TYPE_MIX:
            /* Unimplemented: silence; warning present elsewhere */
        default:
            av_log(log, AV_LOG_ERROR,
                   "Type %d is not implemented\n", s1->type);
            return AVERROR_PATCHWELCOME;
    }
    return 0;
}