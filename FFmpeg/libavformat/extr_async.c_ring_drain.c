#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int read_pos; } ;
typedef  TYPE_1__ RingBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int ring_size (TYPE_1__*) ; 
 int ring_size_of_read_back (TYPE_1__*) ; 

__attribute__((used)) static int ring_drain(RingBuffer *ring, int offset)
{
    av_assert2(offset >= -ring_size_of_read_back(ring));
    av_assert2(offset <= ring_size(ring));
    ring->read_pos += offset;
    return 0;
}