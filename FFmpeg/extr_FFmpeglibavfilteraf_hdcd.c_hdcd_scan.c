#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {unsigned int sustain; int sustain_reset; int count_sustain_expired; scalar_t__ control; } ;
typedef  TYPE_1__ hdcd_state ;
typedef  int /*<<< orphan*/  cdt_active ;
typedef  int /*<<< orphan*/  HDCDContext ;

/* Variables and functions */
 int HDCD_MAX_CHANNELS ; 
 int hdcd_integrate (int /*<<< orphan*/ *,TYPE_1__*,int,int*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdcd_scan(HDCDContext *ctx, hdcd_state *states, int channels, const int32_t *samples, int max, int stride)
{
    int result;
    int i;
    int cdt_active[HDCD_MAX_CHANNELS];
    memset(cdt_active, 0, sizeof(cdt_active));

    if (stride < channels) stride = channels;

    /* code detect timers for each channel */
    for(i = 0; i < channels; i++) {
        if (states[i].sustain > 0) {
            cdt_active[i] = 1;
            if (states[i].sustain <=  (unsigned)max) {
                states[i].control = 0;
                max = states[i].sustain;
            }
            states[i].sustain -= max;
        }
    }

    result = 0;
    while (result < max) {
        int flag;
        int consumed = hdcd_integrate(ctx, states, channels, &flag, samples, max - result, stride);
        result += consumed;
        if (flag) {
            /* reset timer if code detected in a channel */
            for(i = 0; i < channels; i++) {
                if (flag & (1<<i)) {
                    states[i].sustain = states[i].sustain_reset;
                    /* if this is the first reset then change
                     * from never set, to never expired */
                    if (states[i].count_sustain_expired == -1)
                        states[i].count_sustain_expired = 0;
                }
            }
            break;
        }
        samples += consumed * stride;
    }

    for(i = 0; i < channels; i++) {
        /* code detect timer expired */
        if (cdt_active[i] && states[i].sustain == 0)
            states[i].count_sustain_expired++;
    }

    return result;
}