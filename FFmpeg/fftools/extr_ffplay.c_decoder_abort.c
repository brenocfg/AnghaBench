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
struct TYPE_3__ {int /*<<< orphan*/  queue; int /*<<< orphan*/ * decoder_tid; } ;
typedef  int /*<<< orphan*/  FrameQueue ;
typedef  TYPE_1__ Decoder ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_queue_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_queue_abort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_queue_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decoder_abort(Decoder *d, FrameQueue *fq)
{
    packet_queue_abort(d->queue);
    frame_queue_signal(fq);
    SDL_WaitThread(d->decoder_tid, NULL);
    d->decoder_tid = NULL;
    packet_queue_flush(d->queue);
}