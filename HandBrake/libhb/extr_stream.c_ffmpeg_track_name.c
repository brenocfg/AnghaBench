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
struct TYPE_7__ {scalar_t__* value; } ;
struct TYPE_6__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* hb_strdup_printf (char*,char const*) ; 

__attribute__((used)) static const char * ffmpeg_track_name(AVStream * st, const char * lang)
{
    AVDictionaryEntry * t;
    char              * key;

    // Use key with no language extension
    // ffmpeg sets this for "und" entries or when source format
    // doesn't have a language field
    t = av_dict_get(st->metadata, "title", NULL, 0);
    if (t != NULL && t->value[0] != 0)
    {
        return t->value;
    }
    // Try explicit "und" extension
    t = av_dict_get(st->metadata, "title-und", NULL, 0);
    if (t != NULL && t->value[0] != 0)
    {
        return t->value;
    }
    // Try source track language
    key = hb_strdup_printf("title-%s", lang);
    t = av_dict_get(st->metadata, key, NULL, 0);
    free(key);
    if (t != NULL && t->value[0] != 0)
    {
        return t->value;
    }
    while ((t = av_dict_get(st->metadata, "title-", t, AV_DICT_IGNORE_SUFFIX)))
    {
        // Use first available
        if (t != NULL && t->value[0] != 0)
        {
            return t->value;
        }
    }
    return NULL;
}