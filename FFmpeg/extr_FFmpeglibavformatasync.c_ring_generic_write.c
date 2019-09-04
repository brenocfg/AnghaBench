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
struct TYPE_4__ {int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ RingBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int av_fifo_generic_write (int /*<<< orphan*/ ,void*,int,int (*) (void*,void*,int)) ; 
 int ring_space (TYPE_1__*) ; 

__attribute__((used)) static int ring_generic_write(RingBuffer *ring, void *src, int size, int (*func)(void*, void*, int))
{
    av_assert2(size <= ring_space(ring));
    return av_fifo_generic_write(ring->fifo, src, size, func);
}