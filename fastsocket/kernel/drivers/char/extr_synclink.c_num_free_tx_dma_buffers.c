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
struct mgsl_struct {int tx_buffer_count; int tx_dma_buffers_used; } ;

/* Variables and functions */

__attribute__((used)) static int num_free_tx_dma_buffers(struct mgsl_struct *info)
{
	return info->tx_buffer_count - info->tx_dma_buffers_used;
}