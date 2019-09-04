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
struct TYPE_7__ {int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int /*<<< orphan*/  metadata; } ;
typedef  int /*<<< orphan*/  MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mov_write_string_data_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_mdta_ilst_tag(AVIOContext *pb, MOVMuxContext *mov,
                                   AVFormatContext *s)
{
    AVDictionaryEntry *t = NULL;
    int64_t pos = avio_tell(pb);
    int count = 1; /* keys are 1-index based */

    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "ilst");

    while (t = av_dict_get(s->metadata, "", t, AV_DICT_IGNORE_SUFFIX)) {
        int64_t entry_pos = avio_tell(pb);
        avio_wb32(pb, 0); /* size */
        avio_wb32(pb, count); /* key */
        mov_write_string_data_tag(pb, t->value, 0, 1);
        update_size(pb, entry_pos);
        count += 1;
    }
    return update_size(pb, pos);
}