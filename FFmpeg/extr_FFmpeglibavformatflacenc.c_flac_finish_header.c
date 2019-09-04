#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct AVFormatContext {int metadata_header_padding; int nb_streams; int error_recognition; int flags; int /*<<< orphan*/  pb; int /*<<< orphan*/  metadata; TYPE_1__** streams; } ;
struct TYPE_2__ {int /*<<< orphan*/ * priv_data; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int AVFMT_FLAG_BITEXACT ; 
 int AV_EF_EXPLODE ; 
 int av_clip_uintp2 (int,int) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int flac_write_block_comment (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  flac_write_block_padding (int /*<<< orphan*/ ,int,int) ; 
 int flac_write_picture (struct AVFormatContext*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flac_finish_header(struct AVFormatContext *s)
{
    int i, ret, padding = s->metadata_header_padding;
    if (padding < 0)
        padding = 8192;
    /* The FLAC specification states that 24 bits are used to represent the
     * size of a metadata block so we must clip this value to 2^24-1. */
    padding = av_clip_uintp2(padding, 24);

    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        AVPacket *pkt = st->priv_data;
        if (!pkt)
            continue;
        ret = flac_write_picture(s, pkt);
        av_packet_unref(pkt);
        if (ret < 0 && (s->error_recognition & AV_EF_EXPLODE))
            return ret;
    }

    ret = flac_write_block_comment(s->pb, &s->metadata, !padding,
                                   s->flags & AVFMT_FLAG_BITEXACT);
    if (ret)
        return ret;

    /* The command line flac encoder defaults to placing a seekpoint
     * every 10s.  So one might add padding to allow that later
     * but there seems to be no simple way to get the duration here.
     * So just add the amount requested by the user. */
    if (padding)
        flac_write_block_padding(s->pb, padding, 1);

    return 0;
}