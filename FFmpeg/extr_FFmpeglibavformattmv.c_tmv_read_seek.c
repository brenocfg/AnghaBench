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
typedef  int int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int audio_chunk_size; int video_chunk_size; int padding; scalar_t__ stream_index; } ;
typedef  TYPE_1__ TMVContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ TMV_HEADER_SIZE ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tmv_read_seek(AVFormatContext *s, int stream_index,
                         int64_t timestamp, int flags)
{
    TMVContext *tmv = s->priv_data;
    int64_t pos;

    if (stream_index)
        return -1;

    pos = timestamp *
          (tmv->audio_chunk_size + tmv->video_chunk_size + tmv->padding);

    if (avio_seek(s->pb, pos + TMV_HEADER_SIZE, SEEK_SET) < 0)
        return -1;
    tmv->stream_index = 0;
    return 0;
}