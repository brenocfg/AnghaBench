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
struct TYPE_5__ {int frame_count; scalar_t__ loop; scalar_t__ using_webp_anim_encoder; } ;
typedef  TYPE_1__ WebpContext ;
struct TYPE_6__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ ,unsigned int) ; 
 int flush (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int webp_write_trailer(AVFormatContext *s)
{
    unsigned filesize;
    WebpContext *w = s->priv_data;

    if (w->using_webp_anim_encoder) {
        if ((w->frame_count > 1) && w->loop) {  // Write loop count.
            avio_seek(s->pb, 42, SEEK_SET);
            avio_wl16(s->pb, w->loop);
        }
    } else {
        int ret;
        if ((ret = flush(s, 1, AV_NOPTS_VALUE)) < 0)
            return ret;

        filesize = avio_tell(s->pb);
        avio_seek(s->pb, 4, SEEK_SET);
        avio_wl32(s->pb, filesize - 8);
        // Note: without the following, avio only writes 8 bytes to the file.
        avio_seek(s->pb, filesize, SEEK_SET);
    }

    return 0;
}