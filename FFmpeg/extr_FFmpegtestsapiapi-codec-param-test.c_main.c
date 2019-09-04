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
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  avformat_close_input (int /*<<< orphan*/ **) ; 
 int check_video_streams (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int open_and_probe_video_streams (int /*<<< orphan*/ **,char*,int) ; 

int main(int argc, char* argv[])
{
    int ret = 0;
    AVFormatContext *fmt_ctx = NULL;
    AVFormatContext *fmt_ctx_no_decode = NULL;

    if (argc < 2) {
        av_log(NULL, AV_LOG_ERROR, "Usage: %s <input>\n", argv[0]);
        return -1;
    }

    if ((ret = open_and_probe_video_streams(&fmt_ctx_no_decode, argv[1], 0)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Failed to probe '%s' without frame decoding\n", argv[1]);
        goto end;
    }

    if ((ret = open_and_probe_video_streams(&fmt_ctx, argv[1], 1)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Failed to probe '%s' with frame decoding\n", argv[1]);
        goto end;
    }

    ret = check_video_streams(fmt_ctx, fmt_ctx_no_decode);

end:
    avformat_close_input(&fmt_ctx);
    avformat_close_input(&fmt_ctx_no_decode);

    return ret;
}