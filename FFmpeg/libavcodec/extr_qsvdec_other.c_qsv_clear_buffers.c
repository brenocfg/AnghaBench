#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pkt ;
struct TYPE_3__ {int /*<<< orphan*/  input_ref; int /*<<< orphan*/  packet_fifo; } ;
typedef  TYPE_1__ QSVOtherContext ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int av_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qsv_clear_buffers(QSVOtherContext *s)
{
    AVPacket pkt;
    while (av_fifo_size(s->packet_fifo) >= sizeof(pkt)) {
        av_fifo_generic_read(s->packet_fifo, &pkt, sizeof(pkt), NULL);
        av_packet_unref(&pkt);
    }

    av_packet_unref(&s->input_ref);
}