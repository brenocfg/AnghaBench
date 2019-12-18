#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_7__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_metadata_set_album_artist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_metadata_set_artist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_metadata_set_comment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_metadata_set_composer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_metadata_set_description (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_metadata_set_genre (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_metadata_set_long_description (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_metadata_set_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_metadata_set_release_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ffmpeg_decmetadata( AVDictionary *m, hb_title_t *title )
{
    int result = 0;
    AVDictionaryEntry *tag = NULL;
    while ( (tag = av_dict_get(m, "", tag, AV_DICT_IGNORE_SUFFIX)) )
    {
        if ( !strcasecmp( "TITLE", tag->key ) )
        {
            hb_metadata_set_name(title->metadata, tag->value);
            result = 1;
        }
        else if ( !strcasecmp( "ARTIST", tag->key ) )
        {
            hb_metadata_set_artist(title->metadata, tag->value);
            result = 1;
        }
        else if ( !strcasecmp( "DIRECTOR", tag->key ) ||
                  !strcasecmp( "album_artist", tag->key ) )
        {
            hb_metadata_set_album_artist(title->metadata, tag->value);
            result = 1;
        }
        else if ( !strcasecmp( "COMPOSER", tag->key ) )
        {
            hb_metadata_set_composer(title->metadata, tag->value);
            result = 1;
        }
        else if ( !strcasecmp( "DATE_RELEASED", tag->key ) ||
                  !strcasecmp( "date", tag->key ) )
        {
            hb_metadata_set_release_date(title->metadata, tag->value);
            result = 1;
        }
        else if ( !strcasecmp( "SUMMARY", tag->key ) ||
                  !strcasecmp( "comment", tag->key ) )
        {
            hb_metadata_set_comment(title->metadata, tag->value);
            result = 1;
        }
        else if ( !strcasecmp( "GENRE", tag->key ) )
        {
            hb_metadata_set_genre(title->metadata, tag->value);
            result = 1;
        }
        else if ( !strcasecmp( "DESCRIPTION", tag->key ) )
        {
            hb_metadata_set_description(title->metadata, tag->value);
            result = 1;
        }
        else if ( !strcasecmp( "SYNOPSIS", tag->key ) )
        {
            hb_metadata_set_long_description(title->metadata, tag->value);
            result = 1;
        }
    }
    return result;
}