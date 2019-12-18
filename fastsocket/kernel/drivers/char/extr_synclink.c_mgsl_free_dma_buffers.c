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
struct mgsl_struct {int /*<<< orphan*/  tx_buffer_count; int /*<<< orphan*/  tx_buffer_list; int /*<<< orphan*/  rx_buffer_count; int /*<<< orphan*/  rx_buffer_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  mgsl_free_buffer_list_memory (struct mgsl_struct*) ; 
 int /*<<< orphan*/  mgsl_free_frame_memory (struct mgsl_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mgsl_free_dma_buffers( struct mgsl_struct *info )
{
	mgsl_free_frame_memory( info, info->rx_buffer_list, info->rx_buffer_count );
	mgsl_free_frame_memory( info, info->tx_buffer_list, info->tx_buffer_count );
	mgsl_free_buffer_list_memory( info );

}