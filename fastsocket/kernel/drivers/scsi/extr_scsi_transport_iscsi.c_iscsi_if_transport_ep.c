#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ep_handle; } ;
struct TYPE_8__ {int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/  ep_handle; } ;
struct TYPE_7__ {TYPE_2__ ep_disconnect; TYPE_4__ ep_poll; } ;
struct TYPE_5__ {int /*<<< orphan*/  retcode; } ;
struct iscsi_uevent {TYPE_3__ u; TYPE_1__ r; } ;
struct iscsi_transport {int /*<<< orphan*/  (* ep_poll ) (struct iscsi_endpoint*,int /*<<< orphan*/ ) ;} ;
struct iscsi_endpoint {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ISCSI_UEVENT_TRANSPORT_EP_CONNECT 131 
#define  ISCSI_UEVENT_TRANSPORT_EP_CONNECT_THROUGH_HOST 130 
#define  ISCSI_UEVENT_TRANSPORT_EP_DISCONNECT 129 
#define  ISCSI_UEVENT_TRANSPORT_EP_POLL 128 
 int iscsi_if_ep_connect (struct iscsi_transport*,struct iscsi_uevent*,int) ; 
 int iscsi_if_ep_disconnect (struct iscsi_transport*,int /*<<< orphan*/ ) ; 
 struct iscsi_endpoint* iscsi_lookup_endpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct iscsi_endpoint*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iscsi_if_transport_ep(struct iscsi_transport *transport,
		      struct iscsi_uevent *ev, int msg_type)
{
	struct iscsi_endpoint *ep;
	int rc = 0;

	switch (msg_type) {
	case ISCSI_UEVENT_TRANSPORT_EP_CONNECT_THROUGH_HOST:
	case ISCSI_UEVENT_TRANSPORT_EP_CONNECT:
		rc = iscsi_if_ep_connect(transport, ev, msg_type);
		break;
	case ISCSI_UEVENT_TRANSPORT_EP_POLL:
		if (!transport->ep_poll)
			return -EINVAL;

		ep = iscsi_lookup_endpoint(ev->u.ep_poll.ep_handle);
		if (!ep)
			return -EINVAL;

		ev->r.retcode = transport->ep_poll(ep,
						   ev->u.ep_poll.timeout_ms);
		break;
	case ISCSI_UEVENT_TRANSPORT_EP_DISCONNECT:
		rc = iscsi_if_ep_disconnect(transport,
					    ev->u.ep_disconnect.ep_handle);
		break;
	}
	return rc;
}