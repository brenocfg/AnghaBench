#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {char* native_name; char* eng_name; int /*<<< orphan*/  iso639_2; } ;
typedef  TYPE_4__ iso639_lang_t ;
struct TYPE_26__ {int /*<<< orphan*/  list_subtitle; } ;
typedef  TYPE_5__ hb_title_t ;
struct TYPE_24__ {int default_track; void* dest; } ;
struct TYPE_23__ {int num; int den; } ;
struct TYPE_27__ {int id; int extradata_size; int /*<<< orphan*/  track; int /*<<< orphan*/  attributes; TYPE_3__ config; scalar_t__* extradata; int /*<<< orphan*/  name; scalar_t__* iso639_2; int /*<<< orphan*/  source; int /*<<< orphan*/  lang; int /*<<< orphan*/  codec; void* format; TYPE_2__ timebase; } ;
typedef  TYPE_6__ hb_subtitle_t ;
struct TYPE_28__ {TYPE_1__* ffmpeg_ic; } ;
typedef  TYPE_7__ hb_stream_t ;
struct TYPE_30__ {char* value; } ;
struct TYPE_29__ {int disposition; int /*<<< orphan*/  metadata; TYPE_10__* codecpar; } ;
struct TYPE_22__ {TYPE_8__** streams; } ;
struct TYPE_21__ {int codec_id; int extradata_size; int /*<<< orphan*/ * extradata; } ;
typedef  TYPE_8__ AVStream ;
typedef  TYPE_9__ AVDictionaryEntry ;
typedef  TYPE_10__ AVCodecParameters ;

/* Variables and functions */
#define  AV_CODEC_ID_ASS 134 
#define  AV_CODEC_ID_DVD_SUBTITLE 133 
#define  AV_CODEC_ID_EIA_608 132 
#define  AV_CODEC_ID_HDMV_PGS_SUBTITLE 131 
#define  AV_CODEC_ID_MOV_TEXT 130 
#define  AV_CODEC_ID_SUBRIP 129 
#define  AV_CODEC_ID_TEXT 128 
 int AV_DISPOSITION_DEFAULT ; 
 int AV_DISPOSITION_FORCED ; 
 int /*<<< orphan*/  CC608SUB ; 
 int /*<<< orphan*/  HB_SUBTITLE_ATTR_CC ; 
 int /*<<< orphan*/  HB_SUBTITLE_ATTR_DEFAULT ; 
 int /*<<< orphan*/  HB_SUBTITLE_ATTR_FORCED ; 
 void* PASSTHRUSUB ; 
 int /*<<< orphan*/  PGSSUB ; 
 void* PICTURESUB ; 
 void* RENDERSUB ; 
 int /*<<< orphan*/  SSASUB ; 
 void* TEXTSUB ; 
 int /*<<< orphan*/  TX3GSUB ; 
 int /*<<< orphan*/  UTF8SUB ; 
 int /*<<< orphan*/  VOBSUB ; 
 int /*<<< orphan*/  WORK_DECCC608 ; 
 int /*<<< orphan*/  WORK_DECPGSSUB ; 
 int /*<<< orphan*/  WORK_DECSSASUB ; 
 int /*<<< orphan*/  WORK_DECTX3GSUB ; 
 int /*<<< orphan*/  WORK_DECUTF8SUB ; 
 int /*<<< orphan*/  WORK_DECVOBSUB ; 
 TYPE_9__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* calloc (int,int) ; 
 int /*<<< orphan*/  ffmpeg_parse_vobsub_extradata (TYPE_10__*,TYPE_6__*) ; 
 char* ffmpeg_track_name (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_6__*) ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  hb_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 char* hb_subsource_name (int /*<<< orphan*/ ) ; 
 TYPE_4__* lang_for_code2 (char*) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void add_ffmpeg_subtitle( hb_title_t *title, hb_stream_t *stream, int id )
{
    AVStream          * st       = stream->ffmpeg_ic->streams[id];
    AVCodecParameters * codecpar = st->codecpar;
    AVDictionaryEntry * tag_lang = av_dict_get(st->metadata, "language", NULL, 0 );
    iso639_lang_t     * lang = lang_for_code2(tag_lang != NULL ?
                                              tag_lang->value : "und");
    const char        * name = ffmpeg_track_name(st, lang->iso639_2);

    hb_subtitle_t *subtitle = calloc( 1, sizeof(*subtitle) );

    subtitle->id = id;
    // If we ever improve our pipeline to allow other time bases...
    // subtitle->timebase.num = st->time_base.num;
    // subtitle->timebase.den = st->time_base.den;
    subtitle->timebase.num = 1;
    subtitle->timebase.den = 90000;

    switch ( codecpar->codec_id )
    {
        case AV_CODEC_ID_DVD_SUBTITLE:
            subtitle->format = PICTURESUB;
            subtitle->source = VOBSUB;
            subtitle->config.dest = RENDERSUB;  // By default render (burn-in) the VOBSUB.
            subtitle->codec = WORK_DECVOBSUB;
            if (ffmpeg_parse_vobsub_extradata(codecpar, subtitle))
                hb_log( "add_ffmpeg_subtitle: malformed extradata for VOB subtitle track; "
                        "subtitle colors likely to be wrong" );
            break;
        case AV_CODEC_ID_TEXT:
        case AV_CODEC_ID_SUBRIP:
            subtitle->format = TEXTSUB;
            subtitle->source = UTF8SUB;
            subtitle->config.dest = PASSTHRUSUB;
            subtitle->codec = WORK_DECUTF8SUB;
            break;
        case AV_CODEC_ID_MOV_TEXT: // TX3G
            subtitle->format = TEXTSUB;
            subtitle->source = TX3GSUB;
            subtitle->config.dest = PASSTHRUSUB;
            subtitle->codec = WORK_DECTX3GSUB;
            break;
        case AV_CODEC_ID_ASS:
            subtitle->format = TEXTSUB;
            subtitle->source = SSASUB;
            subtitle->config.dest = PASSTHRUSUB;
            subtitle->codec = WORK_DECSSASUB;
            break;
        case AV_CODEC_ID_HDMV_PGS_SUBTITLE:
            subtitle->format = PICTURESUB;
            subtitle->source = PGSSUB;
            subtitle->config.dest = RENDERSUB;
            subtitle->codec = WORK_DECPGSSUB;
            break;
        case AV_CODEC_ID_EIA_608:
            subtitle->format = TEXTSUB;
            subtitle->source = CC608SUB;
            subtitle->config.dest = PASSTHRUSUB;
            subtitle->codec = WORK_DECCC608;
            subtitle->attributes  = HB_SUBTITLE_ATTR_CC;
            break;
        default:
            hb_log( "add_ffmpeg_subtitle: unknown subtitle stream type: 0x%x",
                    (int) codecpar->codec_id );
            free(subtitle);
            return;
    }

    snprintf(subtitle->lang, sizeof( subtitle->lang ), "%s [%s]",
             strlen(lang->native_name) ? lang->native_name : lang->eng_name,
             hb_subsource_name(subtitle->source));
    strncpy(subtitle->iso639_2, lang->iso639_2, 3);
    subtitle->iso639_2[3] = 0;
    if (name != NULL)
    {
        subtitle->name = strdup(name);
    }

    // Copy the extradata for the subtitle track
    if (codecpar->extradata != NULL)
    {
        subtitle->extradata = malloc(codecpar->extradata_size + 1);
        memcpy(subtitle->extradata,
               codecpar->extradata, codecpar->extradata_size);
        subtitle->extradata[codecpar->extradata_size] = 0;
        subtitle->extradata_size = codecpar->extradata_size + 1;
    }

    if (st->disposition & AV_DISPOSITION_DEFAULT)
    {
        subtitle->config.default_track = 1;
        subtitle->attributes |= HB_SUBTITLE_ATTR_DEFAULT;
    }
    if (st->disposition & AV_DISPOSITION_FORCED)
    {
        subtitle->attributes |= HB_SUBTITLE_ATTR_FORCED;
    }

    subtitle->track = hb_list_count(title->list_subtitle);
    hb_list_add(title->list_subtitle, subtitle);
}