#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* src; } ;
struct TYPE_6__ {scalar_t__ eof; int /*<<< orphan*/  fifo; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ BufferSourceContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int av_fifo_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int poll_frame(AVFilterLink *link)
{
    BufferSourceContext *c = link->src->priv;
    int size = av_fifo_size(c->fifo);
    if (!size && c->eof)
        return AVERROR_EOF;
    return size/sizeof(AVFrame*);
}