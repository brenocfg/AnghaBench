#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int tag; int /*<<< orphan*/  tag_pos; } ;
typedef  TYPE_1__ SWFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int TAG_LONG ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_swf_tag(AVFormatContext *s, int tag)
{
    SWFContext *swf = s->priv_data;
    AVIOContext *pb = s->pb;

    swf->tag_pos = avio_tell(pb);
    swf->tag = tag;
    /* reserve some room for the tag */
    if (tag & TAG_LONG) {
        avio_wl16(pb, 0);
        avio_wl32(pb, 0);
    } else {
        avio_wl16(pb, 0);
    }
}