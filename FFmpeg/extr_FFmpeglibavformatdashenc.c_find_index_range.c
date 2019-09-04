#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int (* io_open ) (TYPE_1__*,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 int AV_RB32 (int /*<<< orphan*/ *) ; 
 scalar_t__ AV_RL32 (int /*<<< orphan*/ *) ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_format_io_close (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void find_index_range(AVFormatContext *s, const char *full_path,
                             int64_t pos, int *index_length)
{
    uint8_t buf[8];
    AVIOContext *pb;
    int ret;

    ret = s->io_open(s, &pb, full_path, AVIO_FLAG_READ, NULL);
    if (ret < 0)
        return;
    if (avio_seek(pb, pos, SEEK_SET) != pos) {
        ff_format_io_close(s, &pb);
        return;
    }
    ret = avio_read(pb, buf, 8);
    ff_format_io_close(s, &pb);
    if (ret < 8)
        return;
    if (AV_RL32(&buf[4]) != MKTAG('s', 'i', 'd', 'x'))
        return;
    *index_length = AV_RB32(&buf[0]);
}