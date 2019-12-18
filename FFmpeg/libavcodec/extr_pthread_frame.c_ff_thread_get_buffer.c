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
typedef  int /*<<< orphan*/  ThreadFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int thread_get_buffer_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int ff_thread_get_buffer(AVCodecContext *avctx, ThreadFrame *f, int flags)
{
    int ret = thread_get_buffer_internal(avctx, f, flags);
    if (ret < 0)
        av_log(avctx, AV_LOG_ERROR, "thread_get_buffer() failed\n");
    return ret;
}