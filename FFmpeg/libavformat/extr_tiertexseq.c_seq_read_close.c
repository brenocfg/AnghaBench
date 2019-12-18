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
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_6__ {TYPE_1__* frame_buffers; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ SeqDemuxContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int SEQ_NUM_FRAME_BUFFERS ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int seq_read_close(AVFormatContext *s)
{
    int i;
    SeqDemuxContext *seq = s->priv_data;

    for (i = 0; i < SEQ_NUM_FRAME_BUFFERS; i++)
        av_freep(&seq->frame_buffers[i].data);

    return 0;
}