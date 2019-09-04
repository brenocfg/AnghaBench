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
typedef  int /*<<< orphan*/  AVFifoBuffer ;

/* Variables and functions */
 unsigned int av_fifo_size (int /*<<< orphan*/  const*) ; 
 unsigned int qsv_fifo_item_size () ; 

__attribute__((used)) static inline unsigned int qsv_fifo_size(const AVFifoBuffer* fifo)
{
    return av_fifo_size(fifo) / qsv_fifo_item_size();
}