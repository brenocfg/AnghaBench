#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int read_back_capacity; int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ RingBuffer ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_fifo_alloc (unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ring_init(RingBuffer *ring, unsigned int capacity, int read_back_capacity)
{
    memset(ring, 0, sizeof(RingBuffer));
    ring->fifo = av_fifo_alloc(capacity + read_back_capacity);
    if (!ring->fifo)
        return AVERROR(ENOMEM);

    ring->read_back_capacity = read_back_capacity;
    return 0;
}