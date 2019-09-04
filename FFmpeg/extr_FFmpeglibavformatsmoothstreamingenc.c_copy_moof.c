#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int (* io_open ) (TYPE_1__*,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  EIO ; 
 int FFMIN (scalar_t__,int) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_format_io_close (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int copy_moof(AVFormatContext *s, const char* infile, const char *outfile, int64_t size)
{
    AVIOContext *in, *out;
    int ret = 0;
    if ((ret = s->io_open(s, &in, infile, AVIO_FLAG_READ, NULL)) < 0)
        return ret;
    if ((ret = s->io_open(s, &out, outfile, AVIO_FLAG_WRITE, NULL)) < 0) {
        ff_format_io_close(s, &in);
        return ret;
    }
    while (size > 0) {
        uint8_t buf[8192];
        int n = FFMIN(size, sizeof(buf));
        n = avio_read(in, buf, n);
        if (n <= 0) {
            ret = AVERROR(EIO);
            break;
        }
        avio_write(out, buf, n);
        size -= n;
    }
    avio_flush(out);
    ff_format_io_close(s, &out);
    ff_format_io_close(s, &in);
    return ret;
}