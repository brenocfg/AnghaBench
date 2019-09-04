#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__ codec_type; } ;
struct TYPE_25__ {TYPE_4__* pb; TYPE_1__** streams; TYPE_5__* priv_data; } ;
struct TYPE_24__ {scalar_t__ riff_start; scalar_t__ movi_list; int riff_id; } ;
struct TYPE_23__ {int seekable; } ;
struct TYPE_22__ {scalar_t__ last_dts; int audio_strm_length; int /*<<< orphan*/  packet_count; } ;
struct TYPE_21__ {int stream_index; int size; scalar_t__ dts; scalar_t__ duration; int flags; unsigned char* data; } ;
struct TYPE_20__ {TYPE_7__* codecpar; TYPE_3__* priv_data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVIStream ;
typedef  TYPE_4__ AVIOContext ;
typedef  TYPE_5__ AVIContext ;
typedef  TYPE_6__ AVFormatContext ;
typedef  TYPE_7__ AVCodecParameters ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 scalar_t__ AVI_MAX_RIFF_SIZE ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int AV_PKT_FLAG_KEY ; 
 int avi_add_ientry (TYPE_6__*,int const,int /*<<< orphan*/ *,unsigned int,int) ; 
 scalar_t__ avi_start_new_riff (TYPE_6__*,TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  avi_stream2fourcc (unsigned char*,int const,scalar_t__) ; 
 int /*<<< orphan*/  avi_write_idx1 (TYPE_6__*) ; 
 int /*<<< orphan*/  avi_write_ix (TYPE_6__*) ; 
 scalar_t__ avio_tell (TYPE_4__*) ; 
 int /*<<< orphan*/  avio_w8 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  avio_write (TYPE_4__*,unsigned char*,int) ; 
 int /*<<< orphan*/  ff_end_tag (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static int avi_write_packet_internal(AVFormatContext *s, AVPacket *pkt)
{
    unsigned char tag[5];
    unsigned int flags = 0;
    const int stream_index = pkt->stream_index;
    int size               = pkt->size;
    AVIContext *avi     = s->priv_data;
    AVIOContext *pb     = s->pb;
    AVIStream *avist    = s->streams[stream_index]->priv_data;
    AVCodecParameters *par = s->streams[stream_index]->codecpar;

    if (pkt->dts != AV_NOPTS_VALUE)
        avist->last_dts = pkt->dts + pkt->duration;

    avist->packet_count++;

    // Make sure to put an OpenDML chunk when the file size exceeds the limits
    if ((pb->seekable & AVIO_SEEKABLE_NORMAL) &&
        (avio_tell(pb) - avi->riff_start > AVI_MAX_RIFF_SIZE)) {
        avi_write_ix(s);
        ff_end_tag(pb, avi->movi_list);

        if (avi->riff_id == 1)
            avi_write_idx1(s);

        ff_end_tag(pb, avi->riff_start);
        avi->movi_list = avi_start_new_riff(s, pb, "AVIX", "movi");
    }

    avi_stream2fourcc(tag, stream_index, par->codec_type);
    if (pkt->flags & AV_PKT_FLAG_KEY)
        flags = 0x10;
    if (par->codec_type == AVMEDIA_TYPE_AUDIO)
        avist->audio_strm_length += size;

    if (s->pb->seekable & AVIO_SEEKABLE_NORMAL) {
        int ret;
        ret = avi_add_ientry(s, stream_index, NULL, flags, size);
        if (ret < 0)
            return ret;
    }

    avio_write(pb, tag, 4);
    avio_wl32(pb, size);
    avio_write(pb, pkt->data, size);
    if (size & 1)
        avio_w8(pb, 0);

    return 0;
}