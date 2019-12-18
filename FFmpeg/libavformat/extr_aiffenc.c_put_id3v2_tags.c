#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_16__ {int /*<<< orphan*/  id3v2_version; TYPE_2__* pict_list; } ;
struct TYPE_15__ {int /*<<< orphan*/  metadata_header_padding; int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; } ;
struct TYPE_14__ {struct TYPE_14__* next; int /*<<< orphan*/  pkt; } ;
struct TYPE_13__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ID3v2EncContext ;
typedef  TYPE_2__ AVPacketList ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AIFFOutputContext ;

/* Variables and functions */
 int /*<<< orphan*/  ID3v2_DEFAULT_MAGIC ; 
 int /*<<< orphan*/  MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_id3v2_finish (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_id3v2_start (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_id3v2_write_apic (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_id3v2_write_metadata (TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static int put_id3v2_tags(AVFormatContext *s, AIFFOutputContext *aiff)
{
    int ret;
    uint64_t pos, end, size;
    ID3v2EncContext id3v2 = { 0 };
    AVIOContext *pb = s->pb;
    AVPacketList *pict_list = aiff->pict_list;

    if (!s->metadata && !aiff->pict_list)
        return 0;

    avio_wl32(pb, MKTAG('I', 'D', '3', ' '));
    avio_wb32(pb, 0);
    pos = avio_tell(pb);

    ff_id3v2_start(&id3v2, pb, aiff->id3v2_version, ID3v2_DEFAULT_MAGIC);
    ff_id3v2_write_metadata(s, &id3v2);
    while (pict_list) {
        if ((ret = ff_id3v2_write_apic(s, &id3v2, &pict_list->pkt)) < 0)
            return ret;
        pict_list = pict_list->next;
    }
    ff_id3v2_finish(&id3v2, pb, s->metadata_header_padding);

    end = avio_tell(pb);
    size = end - pos;

    /* Update chunk size */
    avio_seek(pb, pos - 4, SEEK_SET);
    avio_wb32(pb, size);
    avio_seek(pb, end, SEEK_SET);

    if (size & 1)
        avio_w8(pb, 0);

    return 0;
}