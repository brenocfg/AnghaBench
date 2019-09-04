#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  chapter_time ;
typedef  int /*<<< orphan*/  chapter_number ;
struct TYPE_9__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_8__ {int /*<<< orphan*/ * metadata; TYPE_4__ time_base; int /*<<< orphan*/  start; } ;
struct TYPE_7__ {char const* key; char const* value; } ;
typedef  TYPE_1__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_2__ AVChapter ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  EINVAL ; 
 int UINT32_MAX ; 
 int av_dict_count (int /*<<< orphan*/ *) ; 
 TYPE_1__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_make_q (int,int) ; 
 int av_rescale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_rescale_q (int /*<<< orphan*/ ,TYPE_4__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream_put_buffer (int /*<<< orphan*/ **,char const*,int) ; 
 int /*<<< orphan*/  bytestream_put_byte (int /*<<< orphan*/ **,char) ; 
 int /*<<< orphan*/  bytestream_put_le32 (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char const*) ; 

int ff_vorbiscomment_write(uint8_t **p, AVDictionary **m,
                           const char *vendor_string,
                           AVChapter **chapters, unsigned int nb_chapters)
{
    int cm_count = 0;
    bytestream_put_le32(p, strlen(vendor_string));
    bytestream_put_buffer(p, vendor_string, strlen(vendor_string));
    if (chapters && nb_chapters) {
        for (int i = 0; i < nb_chapters; i++) {
            cm_count += av_dict_count(chapters[i]->metadata) + 1;
        }
    }
    if (*m) {
        int count = av_dict_count(*m) + cm_count;
        AVDictionaryEntry *tag = NULL;
        bytestream_put_le32(p, count);
        while ((tag = av_dict_get(*m, "", tag, AV_DICT_IGNORE_SUFFIX))) {
            int64_t len1 = strlen(tag->key);
            int64_t len2 = strlen(tag->value);
            if (len1+1+len2 > UINT32_MAX)
                return AVERROR(EINVAL);
            bytestream_put_le32(p, len1+1+len2);
            bytestream_put_buffer(p, tag->key, len1);
            bytestream_put_byte(p, '=');
            bytestream_put_buffer(p, tag->value, len2);
        }
        for (int i = 0; i < nb_chapters; i++) {
            AVChapter *chp = chapters[i];
            char chapter_time[13];
            char chapter_number[4];
            int h, m, s, ms;

            s  = av_rescale(chp->start, chp->time_base.num, chp->time_base.den);
            h  = s / 3600;
            m  = (s / 60) % 60;
            ms = av_rescale_q(chp->start, chp->time_base, av_make_q(   1, 1000)) % 1000;
            s  = s % 60;
            snprintf(chapter_number, sizeof(chapter_number), "%03d", i);
            snprintf(chapter_time, sizeof(chapter_time), "%02d:%02d:%02d.%03d", h, m, s, ms);
            bytestream_put_le32(p, 10+1+12);
            bytestream_put_buffer(p, "CHAPTER", 7);
            bytestream_put_buffer(p, chapter_number, 3);
            bytestream_put_byte(p, '=');
            bytestream_put_buffer(p, chapter_time, 12);

            tag = NULL;
            while ((tag = av_dict_get(chapters[i]->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
                int64_t len1 = !strcmp(tag->key, "title") ? 4 : strlen(tag->key);
                int64_t len2 = strlen(tag->value);
                if (len1+1+len2+10 > UINT32_MAX)
                    return AVERROR(EINVAL);
                bytestream_put_le32(p, 10+len1+1+len2);
                bytestream_put_buffer(p, "CHAPTER", 7);
                bytestream_put_buffer(p, chapter_number, 3);
                if (!strcmp(tag->key, "title"))
                    bytestream_put_buffer(p, "NAME", 4);
                else
                    bytestream_put_buffer(p, tag->key, len1);
                bytestream_put_byte(p, '=');
                bytestream_put_buffer(p, tag->value, len2);
            }
        }
    } else
        bytestream_put_le32(p, 0);
    return 0;
}