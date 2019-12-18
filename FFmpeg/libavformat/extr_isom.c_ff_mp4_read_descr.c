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
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int ff_mp4_read_descr_len (int /*<<< orphan*/ *) ; 

int ff_mp4_read_descr(AVFormatContext *fc, AVIOContext *pb, int *tag)
{
    int len;
    *tag = avio_r8(pb);
    len = ff_mp4_read_descr_len(pb);
    av_log(fc, AV_LOG_TRACE, "MPEG-4 description: tag=0x%02x len=%d\n", *tag, len);
    return len;
}