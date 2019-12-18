#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {float den; scalar_t__ num; } ;
struct TYPE_16__ {float den; scalar_t__ num; } ;
struct TYPE_14__ {int num; int den; } ;
struct TYPE_15__ {int width; int height; TYPE_1__ par; } ;
struct TYPE_20__ {int index; scalar_t__ type; char* path; int playlist; int angle_count; int hours; int minutes; int seconds; int* crop; scalar_t__ detected_interlacing; int /*<<< orphan*/  list_subtitle; int /*<<< orphan*/  list_audio; int /*<<< orphan*/  list_chapter; TYPE_4__ vrate; TYPE_3__ dar; TYPE_2__ geometry; } ;
typedef  TYPE_7__ hb_title_t ;
struct TYPE_21__ {char* lang; } ;
typedef  TYPE_8__ hb_subtitle_t ;
struct TYPE_22__ {int index; int hours; int minutes; int seconds; } ;
typedef  TYPE_9__ hb_chapter_t ;
struct TYPE_19__ {char* description; char* iso639_2; } ;
struct TYPE_18__ {scalar_t__ codec; int samplerate; int bitrate; } ;
struct TYPE_13__ {TYPE_6__ lang; TYPE_5__ in; } ;
typedef  TYPE_10__ hb_audio_config_t ;

/* Variables and functions */
 scalar_t__ HB_ACODEC_AC3 ; 
 scalar_t__ HB_ACODEC_DCA ; 
 scalar_t__ HB_BD_TYPE ; 
 scalar_t__ HB_DVD_TYPE ; 
 scalar_t__ HB_FF_STREAM_TYPE ; 
 scalar_t__ HB_STREAM_TYPE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_10__* hb_list_audio_config_item (int /*<<< orphan*/ ,int) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 void* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void PrintTitleInfo( hb_title_t * title, int feature )
{
    int i;

    fprintf( stderr, "+ title %d:\n", title->index );
    if ( title->index == feature )
    {
        fprintf( stderr, "  + Main Feature\n" );
    }
    if ( title->type == HB_STREAM_TYPE || title->type == HB_FF_STREAM_TYPE )
    {
        fprintf( stderr, "  + stream: %s\n", title->path );
    }
    else if ( title->type == HB_DVD_TYPE )
    {
        fprintf( stderr, "  + index %d\n", title->index);
    }
    else if( title->type == HB_BD_TYPE )
    {
        fprintf( stderr, "  + playlist: %05d.MPLS\n", title->playlist );
    }
    if (title->angle_count > 1)
        fprintf( stderr, "  + angle(s) %d\n", title->angle_count );
    fprintf( stderr, "  + duration: %02d:%02d:%02d\n",
             title->hours, title->minutes, title->seconds );
    fprintf( stderr, "  + size: %dx%d, pixel aspect: %d/%d, display aspect: %.2f, %.3f fps\n",
             title->geometry.width, title->geometry.height,
             title->geometry.par.num, title->geometry.par.den,
             (float)title->dar.num / title->dar.den,
             (float)title->vrate.num / title->vrate.den );
    fprintf( stderr, "  + autocrop: %d/%d/%d/%d\n", title->crop[0],
             title->crop[1], title->crop[2], title->crop[3] );

    fprintf( stderr, "  + chapters:\n" );
    for( i = 0; i < hb_list_count( title->list_chapter ); i++ )
    {
        hb_chapter_t  * chapter;
        chapter = hb_list_item( title->list_chapter, i );
        fprintf( stderr, "    + %d: duration %02d:%02d:%02d\n",
                 chapter->index, chapter->hours, chapter->minutes,
                 chapter->seconds );
    }
    fprintf( stderr, "  + audio tracks:\n" );
    for( i = 0; i < hb_list_count( title->list_audio ); i++ )
    {
        hb_audio_config_t *audio;
        audio = hb_list_audio_config_item( title->list_audio, i );
        if( ( audio->in.codec == HB_ACODEC_AC3 ) || ( audio->in.codec == HB_ACODEC_DCA) )
        {
            fprintf( stderr, "    + %d, %s (iso639-2: %s), %dHz, %dbps\n",
                     i + 1,
                     audio->lang.description,
                     audio->lang.iso639_2,
                     audio->in.samplerate,
                     audio->in.bitrate );
        }
        else
        {
            fprintf( stderr, "    + %d, %s (iso639-2: %s)\n",
                     i + 1,
                     audio->lang.description,
                     audio->lang.iso639_2 );
        }
    }
    fprintf( stderr, "  + subtitle tracks:\n" );
    for( i = 0; i < hb_list_count( title->list_subtitle ); i++ )
    {
        hb_subtitle_t *subtitle;
        subtitle = hb_list_item( title->list_subtitle, i );
        fprintf(stderr, "    + %d, %s\n", i + 1, subtitle->lang);
    }

    if(title->detected_interlacing)
    {
        /* Interlacing was found in half or more of the preview frames */
        fprintf( stderr, "  + combing detected, may be interlaced or telecined\n");
    }

}