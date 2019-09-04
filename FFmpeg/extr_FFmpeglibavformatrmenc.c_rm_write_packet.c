#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__** streams; } ;
struct TYPE_11__ {size_t stream_index; int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {scalar_t__ codec_type; } ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int rm_write_audio (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rm_write_video (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rm_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    if (s->streams[pkt->stream_index]->codecpar->codec_type ==
        AVMEDIA_TYPE_AUDIO)
        return rm_write_audio(s, pkt->data, pkt->size, pkt->flags);
    else
        return rm_write_video(s, pkt->data, pkt->size, pkt->flags);
}