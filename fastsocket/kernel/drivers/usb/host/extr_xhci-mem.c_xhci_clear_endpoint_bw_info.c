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
struct xhci_bw_info {scalar_t__ max_esit_payload; scalar_t__ type; scalar_t__ max_packet_size; scalar_t__ num_packets; scalar_t__ mult; scalar_t__ ep_interval; } ;

/* Variables and functions */

void xhci_clear_endpoint_bw_info(struct xhci_bw_info *bw_info)
{
	bw_info->ep_interval = 0;
	bw_info->mult = 0;
	bw_info->num_packets = 0;
	bw_info->max_packet_size = 0;
	bw_info->type = 0;
	bw_info->max_esit_payload = 0;
}