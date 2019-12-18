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
struct TYPE_4__ {int entry; int /*<<< orphan*/  audio_vbr; } ;
typedef  TYPE_1__ MOVTrack ;

/* Variables and functions */
 int get_cluster_duration (TYPE_1__*,int) ; 

__attribute__((used)) static int get_samples_per_packet(MOVTrack *track)
{
    int i, first_duration;

// return track->par->frame_size;

    /* use 1 for raw PCM */
    if (!track->audio_vbr)
        return 1;

    /* check to see if duration is constant for all clusters */
    if (!track->entry)
        return 0;
    first_duration = get_cluster_duration(track, 0);
    for (i = 1; i < track->entry; i++) {
        if (get_cluster_duration(track, i) != first_duration)
            return 0;
    }
    return first_duration;
}