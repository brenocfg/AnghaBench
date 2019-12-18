#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_10__ {TYPE_2__* audio_stream; } ;
struct TYPE_9__ {int /*<<< orphan*/  nb_frames; TYPE_1__* par; } ;
struct TYPE_8__ {scalar_t__ codec_id; } ;
typedef  TYPE_2__ StreamInfo ;
typedef  TYPE_3__ RMMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_AC3 ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  write_packet_header (TYPE_4__*,TYPE_2__*,int,int) ; 

__attribute__((used)) static int rm_write_audio(AVFormatContext *s, const uint8_t *buf, int size, int flags)
{
    RMMuxContext *rm = s->priv_data;
    AVIOContext *pb = s->pb;
    StreamInfo *stream = rm->audio_stream;
    int i;

    write_packet_header(s, stream, size, !!(flags & AV_PKT_FLAG_KEY));

    if (stream->par->codec_id == AV_CODEC_ID_AC3) {
        /* for AC-3, the words seem to be reversed */
        for (i = 0; i < size; i += 2) {
            avio_w8(pb, buf[i + 1]);
            avio_w8(pb, buf[i]);
        }
    } else {
        avio_write(pb, buf, size);
    }
    stream->nb_frames++;
    return 0;
}