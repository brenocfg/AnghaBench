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
typedef  int int64_t ;
struct TYPE_7__ {int /*<<< orphan*/ * metadata; } ;
struct TYPE_6__ {char const* key; char const* value; } ;
typedef  TYPE_1__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_2__ AVChapter ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 TYPE_1__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

int64_t ff_vorbiscomment_length(AVDictionary *m, const char *vendor_string,
                                AVChapter **chapters, unsigned int nb_chapters)
{
    int64_t len = 8;
    len += strlen(vendor_string);
    if (chapters && nb_chapters) {
        for (int i = 0; i < nb_chapters; i++) {
            AVDictionaryEntry *tag = NULL;
            len += 4 + 12 + 1 + 10;
            while ((tag = av_dict_get(chapters[i]->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
                int64_t len1 = !strcmp(tag->key, "title") ? 4 : strlen(tag->key);
                len += 4 + 10 + len1 + 1 + strlen(tag->value);
            }
        }
    }
    if (m) {
        AVDictionaryEntry *tag = NULL;
        while ((tag = av_dict_get(m, "", tag, AV_DICT_IGNORE_SUFFIX))) {
            len += 4 +strlen(tag->key) + 1 + strlen(tag->value);
        }
    }
    return len;
}