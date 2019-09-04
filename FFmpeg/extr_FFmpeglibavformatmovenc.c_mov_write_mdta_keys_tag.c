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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
struct TYPE_6__ {int /*<<< orphan*/  metadata; } ;
typedef  int /*<<< orphan*/  MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_mdta_keys_tag(AVIOContext *pb, MOVMuxContext *mov,
                                   AVFormatContext *s)
{
    AVDictionaryEntry *t = NULL;
    int64_t pos = avio_tell(pb);
    int64_t curpos, entry_pos;
    int count = 0;

    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "keys");
    avio_wb32(pb, 0);
    entry_pos = avio_tell(pb);
    avio_wb32(pb, 0); /* entry count */

    while (t = av_dict_get(s->metadata, "", t, AV_DICT_IGNORE_SUFFIX)) {
        avio_wb32(pb, strlen(t->key) + 8);
        ffio_wfourcc(pb, "mdta");
        avio_write(pb, t->key, strlen(t->key));
        count += 1;
    }
    curpos = avio_tell(pb);
    avio_seek(pb, entry_pos, SEEK_SET);
    avio_wb32(pb, count); // rewrite entry count
    avio_seek(pb, curpos, SEEK_SET);

    return update_size(pb, pos);
}