#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tag2 ;
struct TYPE_8__ {int /*<<< orphan*/ * key; int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ff_mov_iso639_to_lang (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static AVDictionaryEntry *get_metadata_lang(AVFormatContext *s,
                                            const char *tag, int *lang)
{
    int l, len, len2;
    AVDictionaryEntry *t, *t2 = NULL;
    char tag2[16];

    *lang = 0;

    if (!(t = av_dict_get(s->metadata, tag, NULL, 0)))
        return NULL;

    len = strlen(t->key);
    snprintf(tag2, sizeof(tag2), "%s-", tag);
    while ((t2 = av_dict_get(s->metadata, tag2, t2, AV_DICT_IGNORE_SUFFIX))) {
        len2 = strlen(t2->key);
        if (len2 == len + 4 && !strcmp(t->value, t2->value)
            && (l = ff_mov_iso639_to_lang(&t2->key[len2 - 3], 1)) >= 0) {
            *lang = l;
            return t;
        }
    }
    return t;
}