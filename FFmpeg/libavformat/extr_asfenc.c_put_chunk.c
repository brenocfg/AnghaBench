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
struct TYPE_5__ {int /*<<< orphan*/  seqno; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ ASFContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_chunk(AVFormatContext *s, int type,
                      int payload_length, int flags)
{
    ASFContext *asf = s->priv_data;
    AVIOContext *pb = s->pb;
    int length;

    length = payload_length + 8;
    avio_wl16(pb, type);
    avio_wl16(pb, length);      // size
    avio_wl32(pb, asf->seqno);  // sequence number
    avio_wl16(pb, flags);       // unknown bytes
    avio_wl16(pb, length);      // size_confirm
    asf->seqno++;
}