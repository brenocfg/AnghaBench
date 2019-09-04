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
typedef  int /*<<< orphan*/  timestamp ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  AVFifoBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ av_fifo_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int64_t timestamp_queue_dequeue(AVFifoBuffer* queue)
{
    int64_t timestamp = AV_NOPTS_VALUE;
    if (av_fifo_size(queue) > 0)
        av_fifo_generic_read(queue, &timestamp, sizeof(timestamp), NULL);

    return timestamp;
}