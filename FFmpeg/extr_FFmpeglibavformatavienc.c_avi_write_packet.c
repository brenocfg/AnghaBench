#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_15__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_34__ {scalar_t__ codec_id; scalar_t__ codec_tag; scalar_t__ codec_type; int bits_per_coded_sample; int width; scalar_t__ format; } ;
struct TYPE_33__ {TYPE_3__* pb; TYPE_15__** streams; } ;
struct TYPE_32__ {int seekable; } ;
struct TYPE_31__ {int* palette; int pal_offset; int strh_flags_offset; int /*<<< orphan*/  old_palette; } ;
struct TYPE_30__ {int stream_index; scalar_t__ size; int /*<<< orphan*/  dts; } ;
struct TYPE_29__ {TYPE_2__* priv_data; TYPE_5__* codecpar; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVIStream ;
typedef  TYPE_3__ AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  AVIIF_NO_TIME ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int AVISF_VIDEO_PALCHANGES ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_RAWVIDEO ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_packet_free (TYPE_1__**) ; 
 int avi_add_ientry (TYPE_4__*,int const,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avi_stream2fourcc (unsigned char*,int const,scalar_t__) ; 
 int avi_write_packet_internal (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int avio_tell (TYPE_3__*) ; 
 int /*<<< orphan*/  avio_w8 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  avio_wb32 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  avio_wl16 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (TYPE_3__*,int) ; 
 int ff_check_h264_startcode (TYPE_4__*,TYPE_15__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ff_end_tag (TYPE_3__*,int) ; 
 int ff_get_packet_palette (TYPE_4__*,TYPE_1__*,int,int*) ; 
 int ff_reshuffle_raw_rgb (TYPE_4__*,TYPE_1__**,TYPE_5__*,int) ; 
 int ff_start_tag (TYPE_3__*,unsigned char*) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int write_skip_frames (TYPE_4__*,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int avi_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    const int stream_index = pkt->stream_index;
    AVCodecParameters *par = s->streams[stream_index]->codecpar;
    int ret;

    if (par->codec_id == AV_CODEC_ID_H264 && par->codec_tag == MKTAG('H','2','6','4') && pkt->size) {
        ret = ff_check_h264_startcode(s, s->streams[stream_index], pkt);
        if (ret < 0)
            return ret;
    }

    if ((ret = write_skip_frames(s, stream_index, pkt->dts)) < 0)
        return ret;

    if (!pkt->size)
        return avi_write_packet_internal(s, pkt); /* Passthrough */

    if (par->codec_type == AVMEDIA_TYPE_VIDEO) {
        AVIStream *avist = s->streams[stream_index]->priv_data;
        AVIOContext *pb  = s->pb;
        AVPacket *opkt   = pkt;
        int reshuffle_ret;
        if (par->codec_id == AV_CODEC_ID_RAWVIDEO && par->codec_tag == 0) {
            int64_t bpc = par->bits_per_coded_sample != 15 ? par->bits_per_coded_sample : 16;
            int expected_stride = ((par->width * bpc + 31) >> 5)*4;
            reshuffle_ret = ff_reshuffle_raw_rgb(s, &pkt, par, expected_stride);
            if (reshuffle_ret < 0)
                return reshuffle_ret;
        } else
            reshuffle_ret = 0;
        if (par->format == AV_PIX_FMT_PAL8) {
            ret = ff_get_packet_palette(s, opkt, reshuffle_ret, avist->palette);
            if (ret < 0)
                goto fail;
            if (ret) {
                int pal_size = 1 << par->bits_per_coded_sample;
                int pc_tag, i;

                av_assert0(par->bits_per_coded_sample >= 0 && par->bits_per_coded_sample <= 8);

                if ((pb->seekable & AVIO_SEEKABLE_NORMAL) && avist->pal_offset) {
                    int64_t cur_offset = avio_tell(pb);
                    avio_seek(pb, avist->pal_offset, SEEK_SET);
                    for (i = 0; i < pal_size; i++) {
                        uint32_t v = avist->palette[i];
                        avio_wl32(pb, v & 0xffffff);
                    }
                    avio_seek(pb, cur_offset, SEEK_SET);
                    memcpy(avist->old_palette, avist->palette, pal_size * 4);
                    avist->pal_offset = 0;
                }
                if (memcmp(avist->palette, avist->old_palette, pal_size * 4)) {
                    unsigned char tag[5];
                    avi_stream2fourcc(tag, stream_index, par->codec_type);
                    tag[2] = 'p'; tag[3] = 'c';
                    if (s->pb->seekable & AVIO_SEEKABLE_NORMAL) {
                        if (avist->strh_flags_offset) {
                            int64_t cur_offset = avio_tell(pb);
                            avio_seek(pb, avist->strh_flags_offset, SEEK_SET);
                            avio_wl32(pb, AVISF_VIDEO_PALCHANGES);
                            avio_seek(pb, cur_offset, SEEK_SET);
                            avist->strh_flags_offset = 0;
                        }
                        ret = avi_add_ientry(s, stream_index, tag, AVIIF_NO_TIME,
                                       pal_size * 4 + 4);
                        if (ret < 0)
                            goto fail;
                    }
                    pc_tag = ff_start_tag(pb, tag);
                    avio_w8(pb, 0);
                    avio_w8(pb, pal_size & 0xFF);
                    avio_wl16(pb, 0); // reserved
                    for (i = 0; i < pal_size; i++) {
                        uint32_t v = avist->palette[i];
                        avio_wb32(pb, v<<8);
                    }
                    ff_end_tag(pb, pc_tag);
                    memcpy(avist->old_palette, avist->palette, pal_size * 4);
                }
            }
        }
        if (reshuffle_ret) {
            ret = avi_write_packet_internal(s, pkt);

fail:
            if (reshuffle_ret)
                av_packet_free(&pkt);
            return ret;
        }
    }

    return avi_write_packet_internal(s, pkt);
}