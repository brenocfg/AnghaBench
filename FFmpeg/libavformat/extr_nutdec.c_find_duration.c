#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  duration_estimation_method; } ;
struct TYPE_5__ {TYPE_2__* avf; } ;
typedef  TYPE_1__ NUTContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVFMT_DURATION_FROM_PTS ; 
 int /*<<< orphan*/  ff_find_last_ts (TYPE_2__*,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nut_read_timestamp ; 

__attribute__((used)) static int64_t find_duration(NUTContext *nut, int64_t filesize)
{
    AVFormatContext *s = nut->avf;
    int64_t duration = 0;

    ff_find_last_ts(s, -1, &duration, NULL, nut_read_timestamp);

    if(duration > 0)
        s->duration_estimation_method = AVFMT_DURATION_FROM_PTS;
    return duration;
}