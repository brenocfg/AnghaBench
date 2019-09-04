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
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  temp_audio_frame; int /*<<< orphan*/  audio_frame; int /*<<< orphan*/  video_frame; int /*<<< orphan*/  blocks_offset_table; int /*<<< orphan*/  frames_offset_table; int /*<<< orphan*/  blocks_count_table; } ;
typedef  TYPE_1__ PAFDemuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_close(AVFormatContext *s)
{
    PAFDemuxContext *p = s->priv_data;

    av_freep(&p->blocks_count_table);
    av_freep(&p->frames_offset_table);
    av_freep(&p->blocks_offset_table);
    av_freep(&p->video_frame);
    av_freep(&p->audio_frame);
    av_freep(&p->temp_audio_frame);

    return 0;
}