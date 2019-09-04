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
typedef  int /*<<< orphan*/  pkt ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVFifoBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  av_fifo_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ av_fifo_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_pkt_fifo(AVFifoBuffer **fifo)
{
    AVPacket pkt;
    while (av_fifo_size(*fifo)) {
        av_fifo_generic_read(*fifo, &pkt, sizeof(pkt), NULL);
        av_packet_unref(&pkt);
    }
    av_fifo_freep(fifo);
}