#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ codec_type; } ;
struct TYPE_13__ {TYPE_1__** streams; } ;
struct TYPE_12__ {size_t stream_index; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_4__* codecpar; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecParameters ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int swf_write_audio (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int swf_write_video (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int swf_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVCodecParameters *par = s->streams[pkt->stream_index]->codecpar;
    if (par->codec_type == AVMEDIA_TYPE_AUDIO)
        return swf_write_audio(s, par, pkt->data, pkt->size);
    else
        return swf_write_video(s, par, pkt->data, pkt->size);
}