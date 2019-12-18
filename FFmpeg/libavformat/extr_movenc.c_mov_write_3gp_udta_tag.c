#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int /*<<< orphan*/  metadata; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  language_code (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf8len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_3gp_udta_tag(AVIOContext *pb, AVFormatContext *s,
                                  const char *tag, const char *str)
{
    int64_t pos = avio_tell(pb);
    AVDictionaryEntry *t = av_dict_get(s->metadata, str, NULL, 0);
    if (!t || !utf8len(t->value))
        return 0;
    avio_wb32(pb, 0);   /* size */
    ffio_wfourcc(pb, tag); /* type */
    avio_wb32(pb, 0);   /* version + flags */
    if (!strcmp(tag, "yrrc"))
        avio_wb16(pb, atoi(t->value));
    else {
        avio_wb16(pb, language_code("eng")); /* language */
        avio_write(pb, t->value, strlen(t->value) + 1); /* UTF8 string value */
        if (!strcmp(tag, "albm") &&
            (t = av_dict_get(s->metadata, "track", NULL, 0)))
            avio_w8(pb, atoi(t->value));
    }
    return update_size(pb, pos);
}