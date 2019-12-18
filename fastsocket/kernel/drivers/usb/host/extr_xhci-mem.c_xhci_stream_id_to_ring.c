#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xhci_virt_ep {TYPE_1__* stream_info; struct xhci_ring* ring; } ;
struct xhci_virt_device {struct xhci_virt_ep* eps; } ;
struct xhci_ring {int dummy; } ;
struct TYPE_2__ {unsigned int num_streams; struct xhci_ring** stream_rings; } ;

/* Variables and functions */

struct xhci_ring *xhci_stream_id_to_ring(
		struct xhci_virt_device *dev,
		unsigned int ep_index,
		unsigned int stream_id)
{
	struct xhci_virt_ep *ep = &dev->eps[ep_index];

	if (stream_id == 0)
		return ep->ring;
	if (!ep->stream_info)
		return NULL;

	if (stream_id > ep->stream_info->num_streams)
		return NULL;
	return ep->stream_info->stream_rings[stream_id];
}