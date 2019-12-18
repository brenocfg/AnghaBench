#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_stream_t ;
struct TYPE_16__ {int probe_next_size; scalar_t__ probe_count; scalar_t__ codec; scalar_t__ codec_param; int stream_type; TYPE_7__* probe_buf; scalar_t__* codec_name; void* stream_kind; } ;
typedef  TYPE_1__ hb_pes_stream_t ;
struct TYPE_17__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ hb_buffer_t ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_21__ {int size; scalar_t__ data; } ;
struct TYPE_20__ {int id; scalar_t__ type; int /*<<< orphan*/  name; } ;
struct TYPE_19__ {int /*<<< orphan*/  name; } ;
struct TYPE_18__ {int buf_size; scalar_t__ buf; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ AVProbeData ;
typedef  TYPE_4__ AVInputFormat ;
typedef  TYPE_5__ AVCodec ;

/* Variables and functions */
 void* A ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AVPROBE_PADDING_SIZE ; 
 int AVPROBE_SCORE_MAX ; 
#define  AV_CODEC_ID_AAC 146 
#define  AV_CODEC_ID_AC3 145 
#define  AV_CODEC_ID_ADPCM_G722 144 
#define  AV_CODEC_ID_CAVS 143 
#define  AV_CODEC_ID_DNXHD 142 
#define  AV_CODEC_ID_DTS 141 
#define  AV_CODEC_ID_EAC3 140 
#define  AV_CODEC_ID_H261 139 
#define  AV_CODEC_ID_H263 138 
#define  AV_CODEC_ID_H264 137 
#define  AV_CODEC_ID_MJPEG 136 
#define  AV_CODEC_ID_MLP 135 
#define  AV_CODEC_ID_MP3 134 
#define  AV_CODEC_ID_MPEG1VIDEO 133 
#define  AV_CODEC_ID_MPEG2VIDEO 132 
#define  AV_CODEC_ID_MPEG4 131 
 scalar_t__ AV_CODEC_ID_NONE ; 
#define  AV_CODEC_ID_SHORTEN 130 
#define  AV_CODEC_ID_TRUEHD 129 
#define  AV_CODEC_ID_VC1 128 
 scalar_t__ HB_ACODEC_AC3 ; 
 scalar_t__ HB_ACODEC_DCA_HD ; 
 scalar_t__ HB_ACODEC_FFMPEG ; 
 scalar_t__ HB_MAX_PROBES ; 
 int HB_MAX_PROBE_SIZE ; 
 void* V ; 
 void* WORK_DECAVCODECV ; 
 TYPE_4__* av_probe_input_format2 (TYPE_3__*,int,int*) ; 
 TYPE_5__* avcodec_find_decoder (int) ; 
 TYPE_5__* avcodec_find_decoder_by_name (int /*<<< orphan*/ ) ; 
 int do_deep_probe (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_7__**) ; 
 void* hb_buffer_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_realloc (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int probe_dts_profile (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_probe(hb_stream_t *stream, hb_pes_stream_t *pes, hb_buffer_t *buf)
{
    int result = 0;

    // Check upper limit of per stream data to probe
    if ( pes->probe_buf == NULL )
    {
        pes->probe_buf = hb_buffer_init( 0 );
        pes->probe_next_size = 0;
        pes->probe_count = 0;
    }

    if ( pes->probe_buf->size > HB_MAX_PROBE_SIZE )
    {
        // Max size reached before finding anything.  Try again from
        // another start PES
        pes->probe_count++;
        hb_buffer_close( &pes->probe_buf );
        if (pes->probe_count >= HB_MAX_PROBES)
        {
            return -1;
        }
        pes->probe_buf = hb_buffer_init( 0 );
        pes->probe_next_size = 0;
    }

    // Add this stream buffer to probe buffer and perform probe
    int size = pes->probe_buf->size + buf->size;

    hb_buffer_realloc(pes->probe_buf, size + AVPROBE_PADDING_SIZE );
    memcpy( pes->probe_buf->data + pes->probe_buf->size, buf->data, buf->size );
    pes->probe_buf->size = size;

    if ( pes->codec == HB_ACODEC_DCA_HD )
    {
        // We need to probe for the profile of DTS audio in this stream.
        return probe_dts_profile( stream, pes );
    }

    // Probing is slow, so we don't want to re-probe the probe
    // buffer for every packet we add to it.  Grow the buffer
    // by a factor of 2 before probing again.
    if ( pes->probe_buf->size < pes->probe_next_size )
        return 0;
    pes->probe_next_size = pes->probe_buf->size * 2;

    if (pes->codec_param != AV_CODEC_ID_NONE)
    {
        // Already did a format probe, but some stream types require a
        // deeper parser probe. E.g. MPEG-1/2, av_probe_input_format2
        // resolves to AV_CODEC_ID_MPEG2VIDEO for both MPEG-1 and MPEG-2
        result = do_deep_probe(stream, pes);
        if (result)
        {
            hb_buffer_close(&pes->probe_buf);
        }
        return result;
    }

    AVInputFormat *fmt = NULL;
    int score = 0;
    AVProbeData pd = {0,};

    pd.buf = pes->probe_buf->data;
    pd.buf_size = pes->probe_buf->size;
    fmt = av_probe_input_format2( &pd, 1, &score );
    if ( fmt && score > AVPROBE_SCORE_MAX / 2 )
    {
        AVCodec *codec = avcodec_find_decoder_by_name( fmt->name );
        if( !codec )
        {
            int i;
            static const struct
            {
                const char *name;
                enum AVCodecID id;
            }
            fmt_id_type[] =
            {
                { "g722"     , AV_CODEC_ID_ADPCM_G722 },
                { "mlp"      , AV_CODEC_ID_MLP        },
                { "truehd"   , AV_CODEC_ID_TRUEHD     },
                { "shn"      , AV_CODEC_ID_SHORTEN    },
                { "aac"      , AV_CODEC_ID_AAC        },
                { "ac3"      , AV_CODEC_ID_AC3        },
                { "dts"      , AV_CODEC_ID_DTS        },
                { "eac3"     , AV_CODEC_ID_EAC3       },
                { "h264"     , AV_CODEC_ID_H264       },
                { "m4v"      , AV_CODEC_ID_MPEG4      },
                { "mp3"      , AV_CODEC_ID_MP3        },
                { "mpegvideo", AV_CODEC_ID_MPEG2VIDEO },
                { "cavsvideo", AV_CODEC_ID_CAVS       },
                { "dnxhd"    , AV_CODEC_ID_DNXHD      },
                { "h261"     , AV_CODEC_ID_H261       },
                { "h263"     , AV_CODEC_ID_H263       },
                { "mjpeg"    , AV_CODEC_ID_MJPEG      },
                { "vc1"      , AV_CODEC_ID_VC1        },
                { 0 },
            };
            for( i = 0; fmt_id_type[i].name; i++ )
            {
                if( !strcmp(fmt->name, fmt_id_type[i].name ) )
                {
                    codec = avcodec_find_decoder( fmt_id_type[i].id );
                    break;
                }
            }
        }
        if( codec )
        {
            pes->codec_param = codec->id;
            if ( codec->type == AVMEDIA_TYPE_VIDEO )
            {
                switch ( codec->id )
                {
                    case AV_CODEC_ID_MPEG1VIDEO:
                        pes->codec = WORK_DECAVCODECV;
                        pes->stream_type = 0x01;
                        pes->stream_kind = V;
                        break;

                    case AV_CODEC_ID_MPEG2VIDEO:
                        pes->codec = WORK_DECAVCODECV;
                        pes->stream_type = 0x02;
                        break;

                    case AV_CODEC_ID_H264:
                        pes->codec = WORK_DECAVCODECV;
                        pes->stream_type = 0x1b;
                        pes->stream_kind = V;
                        break;

                    case AV_CODEC_ID_VC1:
                        pes->codec = WORK_DECAVCODECV;
                        pes->stream_type = 0xea;
                        pes->stream_kind = V;
                        break;

                    default:
                        pes->codec = WORK_DECAVCODECV;
                        pes->stream_kind = V;
                        break;
                }
            }
            else if ( codec->type == AVMEDIA_TYPE_AUDIO )
            {
                pes->stream_kind = A;
                switch ( codec->id )
                {
                    case AV_CODEC_ID_AC3:
                        pes->codec = HB_ACODEC_AC3;
                        break;
                    default:
                        pes->codec = HB_ACODEC_FFMPEG;
                }
            }
            strncpy(pes->codec_name, codec->name, 79);
            pes->codec_name[79] = 0;
        }
        if (pes->codec_param != AV_CODEC_ID_MPEG2VIDEO)
        {
            hb_buffer_close( &pes->probe_buf );
            result = 1;
        }
    }
    return result;
}