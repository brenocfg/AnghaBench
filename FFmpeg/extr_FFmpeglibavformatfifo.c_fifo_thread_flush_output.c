#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* priv_data; } ;
struct TYPE_7__ {TYPE_3__* avf; } ;
struct TYPE_6__ {TYPE_3__* avf; } ;
typedef  TYPE_1__ FifoThreadContext ;
typedef  TYPE_2__ FifoContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int av_write_frame (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fifo_thread_flush_output(FifoThreadContext *ctx)
{
    AVFormatContext *avf = ctx->avf;
    FifoContext *fifo = avf->priv_data;
    AVFormatContext *avf2 = fifo->avf;

    return av_write_frame(avf2, NULL);
}