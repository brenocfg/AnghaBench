#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {char* native_name; char* eng_name; char* iso639_2; } ;
typedef  TYPE_3__ iso639_lang_t ;
struct TYPE_12__ {int num; int den; } ;
struct TYPE_11__ {int /*<<< orphan*/  dest; } ;
struct TYPE_14__ {int track; int stream_type; int /*<<< orphan*/  iso639_2; int /*<<< orphan*/  lang; int /*<<< orphan*/  id; TYPE_2__ timebase; int /*<<< orphan*/  codec; int /*<<< orphan*/  reg_desc; int /*<<< orphan*/  source; TYPE_1__ config; int /*<<< orphan*/  format; } ;
typedef  TYPE_4__ hb_subtitle_t ;
typedef  int /*<<< orphan*/  hb_list_t ;
struct TYPE_15__ {int coding_type; scalar_t__ lang; int /*<<< orphan*/  pid; } ;
typedef  TYPE_5__ BLURAY_STREAM_INFO ;

/* Variables and functions */
#define  BLURAY_STREAM_TYPE_SUB_PG 128 
 int /*<<< orphan*/  PGSSUB ; 
 int /*<<< orphan*/  PICTURESUB ; 
 int /*<<< orphan*/  RENDERSUB ; 
 int /*<<< orphan*/  STR4_TO_UINT32 (char*) ; 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  hb_log (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* hb_subsource_name (int /*<<< orphan*/ ) ; 
 TYPE_3__* lang_for_code2 (char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,...) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void add_subtitle(int track, hb_list_t *list_subtitle, BLURAY_STREAM_INFO *bdsub, uint32_t codec)
{
    hb_subtitle_t * subtitle;
    iso639_lang_t * lang;

    subtitle = calloc( sizeof( hb_subtitle_t ), 1 );

    subtitle->track = track;
    subtitle->id = bdsub->pid;

    switch ( bdsub->coding_type )
    {
        case BLURAY_STREAM_TYPE_SUB_PG:
            subtitle->source = PGSSUB;
            subtitle->format = PICTURESUB;
            subtitle->config.dest = RENDERSUB;
            break;
        default:
            // Unrecognized, don't add to list
            free( subtitle );
            return;
    }
    lang = lang_for_code2( (char*)bdsub->lang );
    snprintf(subtitle->lang, sizeof( subtitle->lang ), "%s [%s]",
             strlen(lang->native_name) ? lang->native_name : lang->eng_name,
             hb_subsource_name(subtitle->source));
    snprintf(subtitle->iso639_2, sizeof( subtitle->iso639_2 ), "%s",
             lang->iso639_2);

    subtitle->reg_desc     = STR4_TO_UINT32("HDMV");
    subtitle->stream_type  = bdsub->coding_type;
    subtitle->codec        = codec;
    subtitle->timebase.num = 1;
    subtitle->timebase.den = 90000;

    hb_log( "bd: subtitle id=0x%x, lang=%s, 3cc=%s", subtitle->id,
            subtitle->lang, subtitle->iso639_2 );

    hb_list_add( list_subtitle, subtitle );
    return;
}