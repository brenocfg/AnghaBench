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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (size_t,int) ; 
 int /*<<< orphan*/  av_bprint_append_data (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  av_bprint_is_complete (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int avio_read_to_bprint(AVIOContext *h, AVBPrint *pb, size_t max_size)
{
    int ret;
    char buf[1024];
    while (max_size) {
        ret = avio_read(h, buf, FFMIN(max_size, sizeof(buf)));
        if (ret == AVERROR_EOF)
            return 0;
        if (ret <= 0)
            return ret;
        av_bprint_append_data(pb, buf, ret);
        if (!av_bprint_is_complete(pb))
            return AVERROR(ENOMEM);
        max_size -= ret;
    }
    return 0;
}