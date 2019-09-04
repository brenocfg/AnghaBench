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
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */

__attribute__((used)) static errno_t
bridge_proto_input(ifnet_t ifp, protocol_family_t protocol, mbuf_t packet,
	char *header)
{
#pragma unused(protocol, packet, header)
#if BRIDGE_DEBUG
	printf("%s: unexpected packet from %s\n", __func__,
	    ifp->if_xname);
#endif /* BRIDGE_DEBUG */
	return (0);
}