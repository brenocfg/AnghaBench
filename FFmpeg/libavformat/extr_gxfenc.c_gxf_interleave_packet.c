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
struct TYPE_14__ {TYPE_2__** streams; } ;
struct TYPE_13__ {size_t stream_index; int duration; } ;
struct TYPE_12__ {TYPE_1__* codecpar; } ;
struct TYPE_11__ {scalar_t__ codec_type; } ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int ff_audio_rechunk_interleave (TYPE_4__*,TYPE_3__*,TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_interleave_packet_per_dts ; 
 int /*<<< orphan*/  gxf_compare_field_nb ; 

__attribute__((used)) static int gxf_interleave_packet(AVFormatContext *s, AVPacket *out, AVPacket *pkt, int flush)
{
    if (pkt && s->streams[pkt->stream_index]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        pkt->duration = 2; // enforce 2 fields
    return ff_audio_rechunk_interleave(s, out, pkt, flush,
                               ff_interleave_packet_per_dts, gxf_compare_field_nb);
}