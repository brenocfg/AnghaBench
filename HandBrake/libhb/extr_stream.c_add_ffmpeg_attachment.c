#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  list_attachment; } ;
typedef  TYPE_2__ hb_title_t ;
struct TYPE_13__ {TYPE_1__* ffmpeg_ic; } ;
typedef  TYPE_3__ hb_stream_t ;
struct TYPE_14__ {int type; int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ hb_attachment_t ;
typedef  enum attachtype { ____Placeholder_attachtype } attachtype ;
struct TYPE_16__ {int codec_id; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  extradata; } ;
struct TYPE_15__ {int /*<<< orphan*/  metadata; TYPE_6__* codecpar; } ;
struct TYPE_11__ {TYPE_5__** streams; } ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVCodecParameters ;

/* Variables and functions */
#define  AV_CODEC_ID_TTF 128 
 int FONT_OTF_ATTACH ; 
 int FONT_TTF_ATTACH ; 
 TYPE_4__* calloc (int,int) ; 
 char* get_ffmpeg_metadata_value (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void add_ffmpeg_attachment( hb_title_t *title, hb_stream_t *stream, int id )
{
    AVStream *st = stream->ffmpeg_ic->streams[id];
    AVCodecParameters *codecpar = st->codecpar;

    enum attachtype type;
    const char *name = get_ffmpeg_metadata_value( st->metadata, "filename" );
    switch ( codecpar->codec_id )
    {
        case AV_CODEC_ID_TTF:
            // FFmpeg sets codec ID based on mime type of the attachment
            type = FONT_TTF_ATTACH;
            break;
        default:
        {
            int len = name ? strlen( name ) : 0;
            if( len >= 4 )
            {
                // Some attachments don't have the right mime type.
                // So also trigger on file name extension.
                if( !strcasecmp( name + len - 4, ".ttc" ) ||
                    !strcasecmp( name + len - 4, ".ttf" ) )
                {
                    type = FONT_TTF_ATTACH;
                    break;
                }
                else if( !strcasecmp( name + len - 4, ".otf" ) )
                {
                    type = FONT_OTF_ATTACH;
                    break;
                }
            }
            // Ignore unrecognized attachment type
            return;
        }
    }

    hb_attachment_t *attachment = calloc( 1, sizeof(*attachment) );

    // Copy the attachment name and data
    attachment->type = type;
    attachment->name = strdup( name );
    attachment->data = malloc( codecpar->extradata_size );
    memcpy( attachment->data, codecpar->extradata, codecpar->extradata_size );
    attachment->size = codecpar->extradata_size;

    hb_list_add(title->list_attachment, attachment);
}