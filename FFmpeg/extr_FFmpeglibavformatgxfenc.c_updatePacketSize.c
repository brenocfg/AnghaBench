#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gxf_write_padding (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int64_t updatePacketSize(AVIOContext *pb, int64_t pos)
{
    int64_t curpos;
    int size;

    size = avio_tell(pb) - pos;
    if (size % 4) {
        gxf_write_padding(pb, 4 - size % 4);
        size = avio_tell(pb) - pos;
    }
    curpos = avio_tell(pb);
    avio_seek(pb, pos + 6, SEEK_SET);
    avio_wb32(pb, size);
    avio_seek(pb, curpos, SEEK_SET);
    return curpos - pos;
}