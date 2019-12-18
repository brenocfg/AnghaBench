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
struct mgsl_struct {scalar_t__ bus_type; int /*<<< orphan*/ * tx_buffer_list; int /*<<< orphan*/ * rx_buffer_list; int /*<<< orphan*/ * buffer_list; int /*<<< orphan*/  buffer_list_dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFERLISTSIZE ; 
 scalar_t__ MGSL_BUS_TYPE_PCI ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mgsl_free_buffer_list_memory( struct mgsl_struct *info )
{
	if (info->buffer_list && info->bus_type != MGSL_BUS_TYPE_PCI)
		dma_free_coherent(NULL, BUFFERLISTSIZE, info->buffer_list, info->buffer_list_dma_addr);
		
	info->buffer_list = NULL;
	info->rx_buffer_list = NULL;
	info->tx_buffer_list = NULL;

}