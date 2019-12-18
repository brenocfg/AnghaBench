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
typedef  int /*<<< orphan*/  frame ;
struct TYPE_8__ {TYPE_1__* src; } ;
struct TYPE_7__ {int /*<<< orphan*/  fifo; int /*<<< orphan*/  nb_failed_requests; scalar_t__ eof; } ;
struct TYPE_6__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ BufferSourceContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_size (int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int request_frame(AVFilterLink *link)
{
    BufferSourceContext *c = link->src->priv;
    AVFrame *frame;
    int ret;

    if (!av_fifo_size(c->fifo)) {
        if (c->eof)
            return AVERROR_EOF;
        c->nb_failed_requests++;
        return AVERROR(EAGAIN);
    }
    av_fifo_generic_read(c->fifo, &frame, sizeof(frame), NULL);

    ret = ff_filter_frame(link, frame);

    return ret;
}