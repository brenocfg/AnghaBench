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
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_16__ {char* native_name; char* eng_name; char* iso639_2; } ;
typedef  TYPE_5__ iso639_lang_t ;
typedef  int /*<<< orphan*/  hb_list_t ;
struct TYPE_13__ {int num; int den; } ;
struct TYPE_14__ {int substream_type; int codec; int track; TYPE_2__ timebase; void* codec_param; int /*<<< orphan*/  stream_type; int /*<<< orphan*/  reg_desc; } ;
struct TYPE_12__ {int /*<<< orphan*/  iso639_2; int /*<<< orphan*/  simple; int /*<<< orphan*/  attributes; } ;
struct TYPE_15__ {TYPE_3__ in; TYPE_1__ lang; } ;
struct TYPE_17__ {int id; TYPE_4__ config; } ;
typedef  TYPE_6__ hb_audio_t ;
struct TYPE_18__ {int pid; scalar_t__ lang; int /*<<< orphan*/  coding_type; } ;
typedef  TYPE_7__ BLURAY_STREAM_INFO ;

/* Variables and functions */
#define  BLURAY_STREAM_TYPE_AUDIO_AC3PLUS 136 
#define  BLURAY_STREAM_TYPE_AUDIO_DTSHD 135 
#define  BLURAY_STREAM_TYPE_AUDIO_DTSHD_MASTER 134 
#define  BLURAY_STREAM_TYPE_AUDIO_LPCM 133 
#define  BLURAY_STREAM_TYPE_AUDIO_MPEG1 132 
#define  BLURAY_STREAM_TYPE_AUDIO_MPEG2 131 
#define  BLURAY_STREAM_TYPE_AUDIO_TRUHD 130 
#define  HB_ACODEC_AC3 129 
#define  HB_ACODEC_DCA 128 
 int HB_ACODEC_FF_MASK ; 
 int /*<<< orphan*/  HB_AUDIO_ATTR_NONE ; 
 int /*<<< orphan*/  STR4_TO_UINT32 (char*) ; 
 TYPE_6__* calloc (int,int) ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  hb_log (char*,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 TYPE_5__* lang_for_code2 (char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void add_audio(int track, hb_list_t *list_audio, BLURAY_STREAM_INFO *bdaudio, int substream_type, uint32_t codec, uint32_t codec_param)
{
    const char * codec_name;
    hb_audio_t * audio;
    iso639_lang_t * lang;

    audio = calloc( sizeof( hb_audio_t ), 1 );

    audio->id = (substream_type << 16) | bdaudio->pid;
    audio->config.in.reg_desc = STR4_TO_UINT32("HDMV");
    audio->config.in.stream_type = bdaudio->coding_type;
    audio->config.in.substream_type = substream_type;
    audio->config.in.codec = codec;
    audio->config.in.codec_param = codec_param;

    switch( audio->config.in.codec )
    {
        case HB_ACODEC_AC3:
            codec_name = "AC3";
            break;
        case HB_ACODEC_DCA:
            codec_name = "DTS";
            break;
        default:
        {
            if( audio->config.in.codec & HB_ACODEC_FF_MASK )
            {
                switch( bdaudio->coding_type )
                {
                    case BLURAY_STREAM_TYPE_AUDIO_AC3PLUS:
                        codec_name = "E-AC3";
                        break;
                    case BLURAY_STREAM_TYPE_AUDIO_DTSHD:
                        codec_name = "DTS-HD HRA";
                        break;
                    case BLURAY_STREAM_TYPE_AUDIO_DTSHD_MASTER:
                        codec_name = "DTS-HD MA";
                        break;
                    case BLURAY_STREAM_TYPE_AUDIO_LPCM:
                        codec_name = "BD LPCM";
                        break;
                    case BLURAY_STREAM_TYPE_AUDIO_MPEG1:
                        codec_name = "MPEG1";
                        break;
                    case BLURAY_STREAM_TYPE_AUDIO_MPEG2:
                        codec_name = "MPEG2";
                        break;
                    case BLURAY_STREAM_TYPE_AUDIO_TRUHD:
                        codec_name = "TrueHD";
                        break;
                    default:
                        codec_name = "Unknown FFmpeg";
                        break;
                }
            }
            else
            {
                codec_name = "Unknown";
            }
        }
        break;
    }

    lang = lang_for_code2( (char*)bdaudio->lang );

    audio->config.lang.attributes = HB_AUDIO_ATTR_NONE;

    snprintf( audio->config.lang.simple,
              sizeof( audio->config.lang.simple ), "%s",
              strlen( lang->native_name ) ? lang->native_name : lang->eng_name );
    snprintf( audio->config.lang.iso639_2,
              sizeof( audio->config.lang.iso639_2 ), "%s", lang->iso639_2 );

    hb_log("bd: audio id=0x%x, lang=%s (%s), 3cc=%s", audio->id,
           audio->config.lang.simple, codec_name, audio->config.lang.iso639_2);

    audio->config.in.track        = track;
    audio->config.in.timebase.num = 1;
    audio->config.in.timebase.den = 90000;

    hb_list_add( list_audio, audio );
    return;
}