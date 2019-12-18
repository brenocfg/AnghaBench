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
struct TYPE_4__ {TYPE_2__* ffmpeg_ic; } ;
typedef  TYPE_1__ hb_stream_t ;
struct TYPE_5__ {scalar_t__ start_time; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 

int64_t ffmpeg_initial_timestamp( hb_stream_t * stream )
{
    AVFormatContext *ic = stream->ffmpeg_ic;
    if (ic->start_time != AV_NOPTS_VALUE)
        return ic->start_time;
    else
        return 0;
}