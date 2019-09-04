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
struct TYPE_10__ {TYPE_2__* pb; TYPE_1__* priv_data; } ;
struct TYPE_9__ {int seekable; } ;
struct TYPE_8__ {int /*<<< orphan*/  frames; } ;
typedef  TYPE_1__ RCVContext ;
typedef  TYPE_2__ AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl24 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc1test_write_trailer(AVFormatContext *s)
{
    RCVContext *ctx = s->priv_data;
    AVIOContext *pb = s->pb;

    if (s->pb->seekable & AVIO_SEEKABLE_NORMAL) {
        avio_seek(pb, 0, SEEK_SET);
        avio_wl24(pb, ctx->frames);
        avio_flush(pb);
    }
    return 0;
}