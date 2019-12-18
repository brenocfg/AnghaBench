#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  ff_asf_guid ;
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_18__ {scalar_t__ codec_id; int codec_type; unsigned int codec_tag; int bits_per_coded_sample; scalar_t__ extradata_size; scalar_t__ extradata; void* height; void* width; } ;
struct TYPE_13__ {scalar_t__ preroll; int flags; int play_time; scalar_t__ file_size; } ;
struct TYPE_17__ {scalar_t__* asfid2avid; TYPE_4__* streams; TYPE_1__ hdr; } ;
struct TYPE_16__ {int ds_span; int ds_packet_size; int ds_chunk_size; int palette_changed; int /*<<< orphan*/ * palette; } ;
struct TYPE_15__ {scalar_t__ nb_streams; int /*<<< orphan*/ * pb; TYPE_5__* priv_data; } ;
struct TYPE_14__ {int id; int request_probe; void* need_parsing; TYPE_7__* codecpar; scalar_t__ duration; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ ASFStream ;
typedef  TYPE_5__ ASFContext ;

/* Variables and functions */
 scalar_t__ ASF_MAX_STREAMS ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVMEDIA_TYPE_AUDIO ; 
 int AVMEDIA_TYPE_DATA ; 
 int AVMEDIA_TYPE_UNKNOWN ; 
 int AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AVPALETTE_SIZE ; 
 void* AVSTREAM_PARSE_FULL ; 
 void* AVSTREAM_PARSE_FULL_ONCE ; 
 void* AVSTREAM_PARSE_NONE ; 
 scalar_t__ AV_CODEC_ID_AAC ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_MJPEG ; 
 scalar_t__ AV_CODEC_ID_MPEG4 ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFABS (scalar_t__) ; 
 int FFMIN (scalar_t__,scalar_t__) ; 
 unsigned int MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_bswap32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (scalar_t__*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_mallocz (scalar_t__) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 void* avio_rl32 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  ff_asf_audio_stream ; 
 int /*<<< orphan*/  ff_asf_command_stream ; 
 int /*<<< orphan*/  ff_asf_ext_stream_audio_stream ; 
 int /*<<< orphan*/  ff_asf_ext_stream_embed_stream_header ; 
 int /*<<< orphan*/  ff_asf_jfif_media ; 
 int /*<<< orphan*/  ff_asf_video_stream ; 
 int /*<<< orphan*/  ff_codec_bmp_tags ; 
 scalar_t__ ff_codec_get_id (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ff_get_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_get_wav_header (TYPE_3__*,int /*<<< orphan*/ *,TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_guidcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ffio_limit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int asf_read_stream_properties(AVFormatContext *s, int64_t size)
{
    ASFContext *asf = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st;
    ASFStream *asf_st;
    ff_asf_guid g;
    enum AVMediaType type;
    int type_specific_size, sizeX;
    unsigned int tag1;
    int64_t pos1, pos2, start_time;
    int test_for_ext_stream_audio, is_dvr_ms_audio = 0;

    if (s->nb_streams == ASF_MAX_STREAMS) {
        av_log(s, AV_LOG_ERROR, "too many streams\n");
        return AVERROR(EINVAL);
    }

    pos1 = avio_tell(pb);

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    avpriv_set_pts_info(st, 32, 1, 1000); /* 32 bit pts in ms */
    start_time     = asf->hdr.preroll;

    if (!(asf->hdr.flags & 0x01)) { // if we aren't streaming...
        int64_t fsize = avio_size(pb);
        if (fsize <= 0 || (int64_t)asf->hdr.file_size <= 0 ||
            20*FFABS(fsize - (int64_t)asf->hdr.file_size) < FFMIN(fsize, asf->hdr.file_size))
            st->duration = asf->hdr.play_time /
                       (10000000 / 1000) - start_time;
    }
    ff_get_guid(pb, &g);

    test_for_ext_stream_audio = 0;
    if (!ff_guidcmp(&g, &ff_asf_audio_stream)) {
        type = AVMEDIA_TYPE_AUDIO;
    } else if (!ff_guidcmp(&g, &ff_asf_video_stream)) {
        type = AVMEDIA_TYPE_VIDEO;
    } else if (!ff_guidcmp(&g, &ff_asf_jfif_media)) {
        type                = AVMEDIA_TYPE_VIDEO;
        st->codecpar->codec_id = AV_CODEC_ID_MJPEG;
    } else if (!ff_guidcmp(&g, &ff_asf_command_stream)) {
        type = AVMEDIA_TYPE_DATA;
    } else if (!ff_guidcmp(&g, &ff_asf_ext_stream_embed_stream_header)) {
        test_for_ext_stream_audio = 1;
        type                      = AVMEDIA_TYPE_UNKNOWN;
    } else {
        return -1;
    }
    ff_get_guid(pb, &g);
    avio_skip(pb, 8); /* total_size */
    type_specific_size = avio_rl32(pb);
    avio_rl32(pb);
    st->id = avio_rl16(pb) & 0x7f; /* stream id */
    // mapping of asf ID to AV stream ID;
    asf->asfid2avid[st->id] = s->nb_streams - 1;
    asf_st = &asf->streams[st->id];

    avio_rl32(pb);

    if (test_for_ext_stream_audio) {
        ff_get_guid(pb, &g);
        if (!ff_guidcmp(&g, &ff_asf_ext_stream_audio_stream)) {
            type            = AVMEDIA_TYPE_AUDIO;
            is_dvr_ms_audio = 1;
            ff_get_guid(pb, &g);
            avio_rl32(pb);
            avio_rl32(pb);
            avio_rl32(pb);
            ff_get_guid(pb, &g);
            avio_rl32(pb);
        }
    }

    st->codecpar->codec_type = type;
    if (type == AVMEDIA_TYPE_AUDIO) {
        int ret = ff_get_wav_header(s, pb, st->codecpar, type_specific_size, 0);
        if (ret < 0)
            return ret;
        if (is_dvr_ms_audio) {
            // codec_id and codec_tag are unreliable in dvr_ms
            // files. Set them later by probing stream.
            st->request_probe    = 1;
            st->codecpar->codec_tag = 0;
        }
        if (st->codecpar->codec_id == AV_CODEC_ID_AAC)
            st->need_parsing = AVSTREAM_PARSE_NONE;
        else
            st->need_parsing = AVSTREAM_PARSE_FULL;
        /* We have to init the frame size at some point .... */
        pos2 = avio_tell(pb);
        if (size >= (pos2 + 8 - pos1 + 24)) {
            asf_st->ds_span        = avio_r8(pb);
            asf_st->ds_packet_size = avio_rl16(pb);
            asf_st->ds_chunk_size  = avio_rl16(pb);
            avio_rl16(pb);  // ds_data_size
            avio_r8(pb);    // ds_silence_data
        }
        if (asf_st->ds_span > 1) {
            if (!asf_st->ds_chunk_size                                ||
                (asf_st->ds_packet_size / asf_st->ds_chunk_size <= 1) ||
                asf_st->ds_packet_size % asf_st->ds_chunk_size)
                asf_st->ds_span = 0;  // disable descrambling
        }
    } else if (type == AVMEDIA_TYPE_VIDEO &&
               size - (avio_tell(pb) - pos1 + 24) >= 51) {
        avio_rl32(pb);
        avio_rl32(pb);
        avio_r8(pb);
        avio_rl16(pb);        /* size */
        sizeX             = avio_rl32(pb); /* size */
        st->codecpar->width  = avio_rl32(pb);
        st->codecpar->height = avio_rl32(pb);
        /* not available for asf */
        avio_rl16(pb); /* panes */
        st->codecpar->bits_per_coded_sample = avio_rl16(pb); /* depth */
        tag1                             = avio_rl32(pb);
        avio_skip(pb, 20);
        if (sizeX > 40) {
            st->codecpar->extradata_size = ffio_limit(pb, sizeX - 40);
            st->codecpar->extradata      = av_mallocz(st->codecpar->extradata_size +
                                                   AV_INPUT_BUFFER_PADDING_SIZE);
            if (!st->codecpar->extradata)
                return AVERROR(ENOMEM);
            avio_read(pb, st->codecpar->extradata, st->codecpar->extradata_size);
        }

        /* Extract palette from extradata if bpp <= 8 */
        /* This code assumes that extradata contains only palette */
        /* This is true for all paletted codecs implemented in libavcodec */
        if (st->codecpar->extradata_size && (st->codecpar->bits_per_coded_sample <= 8)) {
#if HAVE_BIGENDIAN
            int i;
            for (i = 0; i < FFMIN(st->codecpar->extradata_size, AVPALETTE_SIZE) / 4; i++)
                asf_st->palette[i] = av_bswap32(((uint32_t *)st->codecpar->extradata)[i]);
#else
            memcpy(asf_st->palette, st->codecpar->extradata,
                   FFMIN(st->codecpar->extradata_size, AVPALETTE_SIZE));
#endif
            asf_st->palette_changed = 1;
        }

        st->codecpar->codec_tag = tag1;
        st->codecpar->codec_id  = ff_codec_get_id(ff_codec_bmp_tags, tag1);
        if (tag1 == MKTAG('D', 'V', 'R', ' ')) {
            st->need_parsing = AVSTREAM_PARSE_FULL;
            /* issue658 contains wrong w/h and MS even puts a fake seq header
             * with wrong w/h in extradata while a correct one is in the stream.
             * maximum lameness */
            st->codecpar->width      =
                st->codecpar->height = 0;
            av_freep(&st->codecpar->extradata);
            st->codecpar->extradata_size = 0;
        }
        if (st->codecpar->codec_id == AV_CODEC_ID_H264)
            st->need_parsing = AVSTREAM_PARSE_FULL_ONCE;
        if (st->codecpar->codec_id == AV_CODEC_ID_MPEG4)
            st->need_parsing = AVSTREAM_PARSE_FULL_ONCE;
    }
    pos2 = avio_tell(pb);
    avio_skip(pb, size - (pos2 - pos1 + 24));

    return 0;
}