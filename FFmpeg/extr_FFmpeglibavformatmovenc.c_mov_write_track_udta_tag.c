#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int mode; } ;
typedef  TYPE_1__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int MODE_MOV ; 
 int MODE_MP4 ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mov_write_track_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int mov_write_track_udta_tag(AVIOContext *pb, MOVMuxContext *mov,
                                    AVStream *st)
{
    AVIOContext *pb_buf;
    int ret, size;
    uint8_t *buf;

    if (!st)
        return 0;

    ret = avio_open_dyn_buf(&pb_buf);
    if (ret < 0)
        return ret;

    if (mov->mode & (MODE_MP4|MODE_MOV))
        mov_write_track_metadata(pb_buf, st, "name", "title");

    if ((size = avio_close_dyn_buf(pb_buf, &buf)) > 0) {
        avio_wb32(pb, size + 8);
        ffio_wfourcc(pb, "udta");
        avio_write(pb, buf, size);
    }
    av_free(buf);

    return 0;
}