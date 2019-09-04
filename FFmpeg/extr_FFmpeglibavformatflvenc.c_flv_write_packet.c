#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int64_t ;
struct TYPE_34__ {int codec_type; scalar_t__ codec_id; int extradata_size; int* extradata; int width; int height; } ;
struct TYPE_33__ {int event_flags; TYPE_1__** streams; TYPE_3__* priv_data; TYPE_5__* pb; } ;
struct TYPE_32__ {int error; } ;
struct TYPE_31__ {size_t stream_index; int size; unsigned int dts; int flags; char* data; int pts; scalar_t__ duration; } ;
struct TYPE_30__ {unsigned int delay; int reserved; int flags; int videosize; int lasttimestamp; int acurframeindex; int framerate; int lastkeyframetimestamp; int lastkeyframelocation; int audiosize; int /*<<< orphan*/  duration; scalar_t__ video_par; } ;
struct TYPE_29__ {unsigned int last_ts; } ;
struct TYPE_28__ {int /*<<< orphan*/  nb_frames; TYPE_2__* priv_data; TYPE_7__* codecpar; } ;
typedef  TYPE_2__ FLVStreamContext ;
typedef  TYPE_3__ FLVContext ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;
typedef  TYPE_7__ AVCodecParameters ;

/* Variables and functions */
 int AMF_DATA_TYPE_MIXEDARRAY ; 
 int AMF_DATA_TYPE_STRING ; 
 int AMF_END_OF_OBJECT ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVIO_DATA_MARKER_BOUNDARY_POINT ; 
 int /*<<< orphan*/  AVIO_DATA_MARKER_SYNC_POINT ; 
#define  AVMEDIA_TYPE_AUDIO 131 
#define  AVMEDIA_TYPE_DATA 130 
#define  AVMEDIA_TYPE_SUBTITLE 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int AVSTREAM_EVENT_FLAG_METADATA_UPDATED ; 
 scalar_t__ AV_CODEC_ID_AAC ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_MPEG4 ; 
 scalar_t__ AV_CODEC_ID_SPEEX ; 
 scalar_t__ AV_CODEC_ID_TEXT ; 
 scalar_t__ AV_CODEC_ID_VP6 ; 
 scalar_t__ AV_CODEC_ID_VP6A ; 
 scalar_t__ AV_CODEC_ID_VP6F ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 unsigned int AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_PKT_DATA_NEW_EXTRADATA ; 
 int AV_PKT_FLAG_KEY ; 
 int AV_RB16 (char*) ; 
 int /*<<< orphan*/  AV_TIME_BASE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int,int) ; 
 int /*<<< orphan*/  FFMAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int FLV_ADD_KEYFRAME_INDEX ; 
 int FLV_FRAME_INTER ; 
 int FLV_FRAME_KEY ; 
 int FLV_TAG_TYPE_AUDIO ; 
 int FLV_TAG_TYPE_META ; 
 int FLV_TAG_TYPE_VIDEO ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  av_free (int*) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 int* av_mallocz (scalar_t__) ; 
 int* av_packet_get_side_data (TYPE_4__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  av_rescale (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avio_seek (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int avio_tell (TYPE_5__*) ; 
 int /*<<< orphan*/  avio_w8 (TYPE_5__*,int) ; 
 int /*<<< orphan*/  avio_wb24 (TYPE_5__*,int) ; 
 int /*<<< orphan*/  avio_wb32 (TYPE_5__*,int) ; 
 int /*<<< orphan*/  avio_write (TYPE_5__*,int*,int) ; 
 int /*<<< orphan*/  avio_write_marker (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_avc_parse_nal_units_buf (char*,int**,int*) ; 
 int ff_codec_get_tag (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  flv_append_keyframe_info (TYPE_6__*,TYPE_3__*,double,int) ; 
 int /*<<< orphan*/  flv_video_codec_ids ; 
 int /*<<< orphan*/  flv_write_codec_header (TYPE_6__*,TYPE_7__*,unsigned int) ; 
 int get_audio_flags (TYPE_6__*,TYPE_7__*) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  put_amf_string (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  put_timestamp (TYPE_5__*,unsigned int) ; 
 int /*<<< orphan*/  write_metadata (TYPE_6__*,unsigned int) ; 

__attribute__((used)) static int flv_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVIOContext *pb      = s->pb;
    AVCodecParameters *par = s->streams[pkt->stream_index]->codecpar;
    FLVContext *flv      = s->priv_data;
    FLVStreamContext *sc = s->streams[pkt->stream_index]->priv_data;
    unsigned ts;
    int size = pkt->size;
    uint8_t *data = NULL;
    int flags = -1, flags_size, ret;
    int64_t cur_offset = avio_tell(pb);

    if (par->codec_type == AVMEDIA_TYPE_AUDIO && !pkt->size) {
        av_log(s, AV_LOG_WARNING, "Empty audio Packet\n");
        return AVERROR(EINVAL);
    }

    if (par->codec_id == AV_CODEC_ID_VP6F || par->codec_id == AV_CODEC_ID_VP6A ||
        par->codec_id == AV_CODEC_ID_VP6  || par->codec_id == AV_CODEC_ID_AAC)
        flags_size = 2;
    else if (par->codec_id == AV_CODEC_ID_H264 || par->codec_id == AV_CODEC_ID_MPEG4)
        flags_size = 5;
    else
        flags_size = 1;

    if (par->codec_id == AV_CODEC_ID_AAC || par->codec_id == AV_CODEC_ID_H264
            || par->codec_id == AV_CODEC_ID_MPEG4) {
        int side_size = 0;
        uint8_t *side = av_packet_get_side_data(pkt, AV_PKT_DATA_NEW_EXTRADATA, &side_size);
        if (side && side_size > 0 && (side_size != par->extradata_size || memcmp(side, par->extradata, side_size))) {
            av_free(par->extradata);
            par->extradata = av_mallocz(side_size + AV_INPUT_BUFFER_PADDING_SIZE);
            if (!par->extradata) {
                par->extradata_size = 0;
                return AVERROR(ENOMEM);
            }
            memcpy(par->extradata, side, side_size);
            par->extradata_size = side_size;
            flv_write_codec_header(s, par, pkt->dts);
        }
    }

    if (flv->delay == AV_NOPTS_VALUE)
        flv->delay = -pkt->dts;

    if (pkt->dts < -flv->delay) {
        av_log(s, AV_LOG_WARNING,
               "Packets are not in the proper order with respect to DTS\n");
        return AVERROR(EINVAL);
    }

    ts = pkt->dts;

    if (s->event_flags & AVSTREAM_EVENT_FLAG_METADATA_UPDATED) {
        write_metadata(s, ts);
        s->event_flags &= ~AVSTREAM_EVENT_FLAG_METADATA_UPDATED;
    }

    avio_write_marker(pb, av_rescale(ts, AV_TIME_BASE, 1000),
                      pkt->flags & AV_PKT_FLAG_KEY && (flv->video_par ? par->codec_type == AVMEDIA_TYPE_VIDEO : 1) ? AVIO_DATA_MARKER_SYNC_POINT : AVIO_DATA_MARKER_BOUNDARY_POINT);

    switch (par->codec_type) {
    case AVMEDIA_TYPE_VIDEO:
        avio_w8(pb, FLV_TAG_TYPE_VIDEO);

        flags = ff_codec_get_tag(flv_video_codec_ids, par->codec_id);

        flags |= pkt->flags & AV_PKT_FLAG_KEY ? FLV_FRAME_KEY : FLV_FRAME_INTER;
        break;
    case AVMEDIA_TYPE_AUDIO:
        flags = get_audio_flags(s, par);

        av_assert0(size);

        avio_w8(pb, FLV_TAG_TYPE_AUDIO);
        break;
    case AVMEDIA_TYPE_SUBTITLE:
    case AVMEDIA_TYPE_DATA:
        avio_w8(pb, FLV_TAG_TYPE_META);
        break;
    default:
        return AVERROR(EINVAL);
    }

    if (par->codec_id == AV_CODEC_ID_H264 || par->codec_id == AV_CODEC_ID_MPEG4) {
        /* check if extradata looks like mp4 formatted */
        if (par->extradata_size > 0 && *(uint8_t*)par->extradata != 1)
            if ((ret = ff_avc_parse_nal_units_buf(pkt->data, &data, &size)) < 0)
                return ret;
    } else if (par->codec_id == AV_CODEC_ID_AAC && pkt->size > 2 &&
               (AV_RB16(pkt->data) & 0xfff0) == 0xfff0) {
        if (!s->streams[pkt->stream_index]->nb_frames) {
        av_log(s, AV_LOG_ERROR, "Malformed AAC bitstream detected: "
               "use the audio bitstream filter 'aac_adtstoasc' to fix it "
               "('-bsf:a aac_adtstoasc' option with ffmpeg)\n");
        return AVERROR_INVALIDDATA;
        }
        av_log(s, AV_LOG_WARNING, "aac bitstream error\n");
    }

    /* check Speex packet duration */
    if (par->codec_id == AV_CODEC_ID_SPEEX && ts - sc->last_ts > 160)
        av_log(s, AV_LOG_WARNING, "Warning: Speex stream has more than "
                                  "8 frames per packet. Adobe Flash "
                                  "Player cannot handle this!\n");

    if (sc->last_ts < ts)
        sc->last_ts = ts;

    if (size + flags_size >= 1<<24) {
        av_log(s, AV_LOG_ERROR, "Too large packet with size %u >= %u\n",
               size + flags_size, 1<<24);
        return AVERROR(EINVAL);
    }

    avio_wb24(pb, size + flags_size);
    put_timestamp(pb, ts);
    avio_wb24(pb, flv->reserved);

    if (par->codec_type == AVMEDIA_TYPE_DATA ||
        par->codec_type == AVMEDIA_TYPE_SUBTITLE ) {
        int data_size;
        int64_t metadata_size_pos = avio_tell(pb);
        if (par->codec_id == AV_CODEC_ID_TEXT) {
            // legacy FFmpeg magic?
            avio_w8(pb, AMF_DATA_TYPE_STRING);
            put_amf_string(pb, "onTextData");
            avio_w8(pb, AMF_DATA_TYPE_MIXEDARRAY);
            avio_wb32(pb, 2);
            put_amf_string(pb, "type");
            avio_w8(pb, AMF_DATA_TYPE_STRING);
            put_amf_string(pb, "Text");
            put_amf_string(pb, "text");
            avio_w8(pb, AMF_DATA_TYPE_STRING);
            put_amf_string(pb, pkt->data);
            put_amf_string(pb, "");
            avio_w8(pb, AMF_END_OF_OBJECT);
        } else {
            // just pass the metadata through
            avio_write(pb, data ? data : pkt->data, size);
        }
        /* write total size of tag */
        data_size = avio_tell(pb) - metadata_size_pos;
        avio_seek(pb, metadata_size_pos - 10, SEEK_SET);
        avio_wb24(pb, data_size);
        avio_seek(pb, data_size + 10 - 3, SEEK_CUR);
        avio_wb32(pb, data_size + 11);
    } else {
        av_assert1(flags>=0);
        avio_w8(pb,flags);
        if (par->codec_id == AV_CODEC_ID_VP6)
            avio_w8(pb,0);
        if (par->codec_id == AV_CODEC_ID_VP6F || par->codec_id == AV_CODEC_ID_VP6A) {
            if (par->extradata_size)
                avio_w8(pb, par->extradata[0]);
            else
                avio_w8(pb, ((FFALIGN(par->width,  16) - par->width) << 4) |
                             (FFALIGN(par->height, 16) - par->height));
        } else if (par->codec_id == AV_CODEC_ID_AAC)
            avio_w8(pb, 1); // AAC raw
        else if (par->codec_id == AV_CODEC_ID_H264 || par->codec_id == AV_CODEC_ID_MPEG4) {
            avio_w8(pb, 1); // AVC NALU
            avio_wb24(pb, pkt->pts - pkt->dts);
        }

        avio_write(pb, data ? data : pkt->data, size);

        avio_wb32(pb, size + flags_size + 11); // previous tag size
        flv->duration = FFMAX(flv->duration,
                              pkt->pts + flv->delay + pkt->duration);
    }

    if (flv->flags & FLV_ADD_KEYFRAME_INDEX) {
        switch (par->codec_type) {
            case AVMEDIA_TYPE_VIDEO:
                flv->videosize += (avio_tell(pb) - cur_offset);
                flv->lasttimestamp = flv->acurframeindex / flv->framerate;
                if (pkt->flags & AV_PKT_FLAG_KEY) {
                    double ts = flv->acurframeindex / flv->framerate;
                    int64_t pos = cur_offset;

                    flv->lastkeyframetimestamp = flv->acurframeindex / flv->framerate;
                    flv->lastkeyframelocation = pos;
                    flv_append_keyframe_info(s, flv, ts, pos);
                }
                flv->acurframeindex++;
                break;

            case AVMEDIA_TYPE_AUDIO:
                flv->audiosize += (avio_tell(pb) - cur_offset);
                break;

            default:
                av_log(s, AV_LOG_WARNING, "par->codec_type is type = [%d]\n", par->codec_type);
                break;
        }
    }

    av_free(data);

    return pb->error;
}