#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* priv_data; TYPE_2__* pb; } ;
struct TYPE_9__ {int seekable; } ;
struct TYPE_8__ {int frame_cnt; int sum_delta_pts; } ;
typedef  TYPE_1__ IVFEncContext ;
typedef  TYPE_2__ AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 size_t avio_tell (TYPE_2__*) ; 
 int /*<<< orphan*/  avio_wl32 (TYPE_2__*,int) ; 

__attribute__((used)) static int ivf_write_trailer(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    IVFEncContext *ctx = s->priv_data;

    if ((pb->seekable & AVIO_SEEKABLE_NORMAL) && ctx->frame_cnt > 1) {
        size_t end = avio_tell(pb);

        avio_seek(pb, 24, SEEK_SET);
        // overwrite the "length" field (duration)
        avio_wl32(pb, ctx->frame_cnt * ctx->sum_delta_pts / (ctx->frame_cnt - 1));
        avio_wl32(pb, 0); // zero out unused bytes
        avio_seek(pb, end, SEEK_SET);
    }

    return 0;
}