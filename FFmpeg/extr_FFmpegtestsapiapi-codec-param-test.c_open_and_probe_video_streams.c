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
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int avformat_open_input (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_video_streams (int /*<<< orphan*/ *,int) ; 
 int find_video_stream_info (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int open_and_probe_video_streams(AVFormatContext **fmt_ctx, const char *filename, int decode)
{
    int ret = 0;

    ret = avformat_open_input(fmt_ctx, filename, NULL, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Failed to open input '%s'", filename);
        goto end;
    }

    ret = find_video_stream_info(*fmt_ctx, decode);
    if (ret < 0) {
        goto end;
    }

    dump_video_streams(*fmt_ctx, decode);

end:
    return ret;
}