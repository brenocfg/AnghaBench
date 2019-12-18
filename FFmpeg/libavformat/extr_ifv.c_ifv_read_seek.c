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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {unsigned int nb_streams; int /*<<< orphan*/ * streams; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int next_video_index; int total_vframes; int next_audio_index; int total_aframes; unsigned int video_stream_index; } ;
typedef  TYPE_1__ IFVContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVSEEK_FLAG_ANY ; 
 int av_index_search_timestamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ifv_read_seek(AVFormatContext *s, int stream_index, int64_t ts, int flags)
{
    IFVContext *ifv = s->priv_data;

    for (unsigned i = 0; i < s->nb_streams; i++) {
        int index = av_index_search_timestamp(s->streams[i], ts, AVSEEK_FLAG_ANY);
        if (index < 0) {
            ifv->next_video_index = ifv->total_vframes - 1;
            ifv->next_audio_index = ifv->total_aframes - 1;
            return 0;
        }

        if (i == ifv->video_stream_index) {
            ifv->next_video_index = index;
        } else {
            ifv->next_audio_index = index;
        }
    }

    return 0;
}