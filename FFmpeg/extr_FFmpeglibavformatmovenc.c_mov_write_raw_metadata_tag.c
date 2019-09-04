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
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int /*<<< orphan*/  metadata; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char const*) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_raw_metadata_tag(AVFormatContext *s, AVIOContext *pb,
                                      const char *name, const char *key)
{
    int len;
    AVDictionaryEntry *t;

    if (!(t = av_dict_get(s->metadata, key, NULL, 0)))
        return 0;

    len = strlen(t->value);
    if (len > 0) {
        int size = len + 8;
        avio_wb32(pb, size);
        ffio_wfourcc(pb, name);
        avio_write(pb, t->value, len);
        return size;
    }
    return 0;
}