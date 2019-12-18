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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ebml_master ;
struct TYPE_6__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tags_bc; int /*<<< orphan*/  seekhead; } ;
typedef  TYPE_1__ MatroskaMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  MATROSKA_ID_TAG ; 
 int /*<<< orphan*/  MATROSKA_ID_TAGS ; 
 int /*<<< orphan*/  MATROSKA_ID_TAGTARGETS ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_ebml_master (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mkv_add_seekhead_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ebml_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  start_ebml_master (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_ebml_master_crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mkv_write_tag_targets(AVFormatContext *s, uint32_t elementid,
                                 unsigned int uid, ebml_master *tag)
{
    AVIOContext *pb;
    MatroskaMuxContext *mkv = s->priv_data;
    ebml_master targets;
    int ret;

    if (!mkv->tags_bc) {
        ret = mkv_add_seekhead_entry(mkv->seekhead, MATROSKA_ID_TAGS, avio_tell(s->pb));
        if (ret < 0) return ret;

        start_ebml_master_crc32(s->pb, &mkv->tags_bc, mkv, MATROSKA_ID_TAGS);
    }
    pb = mkv->tags_bc;

    *tag    = start_ebml_master(pb, MATROSKA_ID_TAG,        0);
    targets = start_ebml_master(pb, MATROSKA_ID_TAGTARGETS, 0);
    if (elementid)
        put_ebml_uint(pb, elementid, uid);
    end_ebml_master(pb, targets);
    return 0;
}