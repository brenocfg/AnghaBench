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
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int entry; scalar_t__ track_duration; scalar_t__ start_dts; TYPE_1__* cluster; } ;
struct TYPE_4__ {scalar_t__ dts; } ;
typedef  TYPE_2__ MOVTrack ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static int get_cluster_duration(MOVTrack *track, int cluster_idx)
{
    int64_t next_dts;

    if (cluster_idx >= track->entry)
        return 0;

    if (cluster_idx + 1 == track->entry)
        next_dts = track->track_duration + track->start_dts;
    else
        next_dts = track->cluster[cluster_idx + 1].dts;

    next_dts -= track->cluster[cluster_idx].dts;

    av_assert0(next_dts >= 0);
    av_assert0(next_dts <= INT_MAX);

    return next_dts;
}