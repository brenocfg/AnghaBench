#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int den; int num; } ;
struct TYPE_5__ {int* audio_samples_dist; TYPE_1__ time_base; } ;
typedef  TYPE_2__ AVDVProfile ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static int dv_audio_frame_size(const AVDVProfile* sys, int frame, int sample_rate)
{
    if ((sys->time_base.den == 25 || sys->time_base.den == 50) && sys->time_base.num == 1) {
        if      (sample_rate == 32000) return 1280;
        else if (sample_rate == 44100) return 1764;
        else                           return 1920;
    }

    av_assert0(sample_rate == 48000);

    return sys->audio_samples_dist[frame % (sizeof(sys->audio_samples_dist) /
                                            sizeof(sys->audio_samples_dist[0]))];
}