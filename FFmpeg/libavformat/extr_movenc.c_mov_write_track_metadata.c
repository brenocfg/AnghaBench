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
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf8len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_track_metadata(AVIOContext *pb, AVStream *st,
                                    const char *tag, const char *str)
{
    int64_t pos = avio_tell(pb);
    AVDictionaryEntry *t = av_dict_get(st->metadata, str, NULL, 0);
    if (!t || !utf8len(t->value))
        return 0;

    avio_wb32(pb, 0);   /* size */
    ffio_wfourcc(pb, tag); /* type */
    avio_write(pb, t->value, strlen(t->value)); /* UTF8 string value */
    return update_size(pb, pos);
}