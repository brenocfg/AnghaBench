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
typedef  int /*<<< orphan*/  AVSubtitle ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int avcodec_decode_subtitle2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avsubtitle_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int subtitle_handler(AVCodecContext *avctx, void *frame,
                            int *got_sub_ptr, AVPacket *avpkt)
{
    AVSubtitle sub;
    int ret = avcodec_decode_subtitle2(avctx, &sub, got_sub_ptr, avpkt);
    if (ret >= 0 && *got_sub_ptr)
        avsubtitle_free(&sub);
    return ret;
}