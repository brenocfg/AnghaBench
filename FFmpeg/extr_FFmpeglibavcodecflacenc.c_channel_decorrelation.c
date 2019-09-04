#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_8__ {scalar_t__ ch_mode; } ;
struct TYPE_10__ {int blocksize; scalar_t__ ch_mode; TYPE_3__* subframes; } ;
struct TYPE_11__ {int channels; TYPE_2__ options; TYPE_4__ frame; } ;
struct TYPE_7__ {int coding_mode; } ;
struct TYPE_9__ {int* samples; int /*<<< orphan*/  obits; TYPE_1__ rc; } ;
typedef  TYPE_4__ FlacFrame ;
typedef  TYPE_5__ FlacEncodeContext ;

/* Variables and functions */
 scalar_t__ FLAC_CHMODE_INDEPENDENT ; 
 scalar_t__ FLAC_CHMODE_LEFT_SIDE ; 
 scalar_t__ FLAC_CHMODE_MID_SIDE ; 
 scalar_t__ estimate_stereo_mode (int*,int*,int,int) ; 

__attribute__((used)) static void channel_decorrelation(FlacEncodeContext *s)
{
    FlacFrame *frame;
    int32_t *left, *right;
    int i, n;

    frame = &s->frame;
    n     = frame->blocksize;
    left  = frame->subframes[0].samples;
    right = frame->subframes[1].samples;

    if (s->channels != 2) {
        frame->ch_mode = FLAC_CHMODE_INDEPENDENT;
        return;
    }

    if (s->options.ch_mode < 0) {
        int max_rice_param = (1 << frame->subframes[0].rc.coding_mode) - 2;
        frame->ch_mode = estimate_stereo_mode(left, right, n, max_rice_param);
    } else
        frame->ch_mode = s->options.ch_mode;

    /* perform decorrelation and adjust bits-per-sample */
    if (frame->ch_mode == FLAC_CHMODE_INDEPENDENT)
        return;
    if (frame->ch_mode == FLAC_CHMODE_MID_SIDE) {
        int32_t tmp;
        for (i = 0; i < n; i++) {
            tmp      = left[i];
            left[i]  = (tmp + right[i]) >> 1;
            right[i] =  tmp - right[i];
        }
        frame->subframes[1].obits++;
    } else if (frame->ch_mode == FLAC_CHMODE_LEFT_SIDE) {
        for (i = 0; i < n; i++)
            right[i] = left[i] - right[i];
        frame->subframes[1].obits++;
    } else {
        for (i = 0; i < n; i++)
            left[i] -= right[i];
        frame->subframes[0].obits++;
    }
}