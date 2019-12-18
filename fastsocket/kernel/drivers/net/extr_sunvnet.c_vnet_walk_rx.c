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
typedef  scalar_t__ u32 ;
struct vio_driver_state {int dummy; } ;
struct vnet_port {struct vio_driver_state vio; } ;
struct vio_dring_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int ECONNRESET ; 
 int /*<<< orphan*/  VIO_DRING_ACTIVE ; 
 int /*<<< orphan*/  VIO_DRING_STOPPED ; 
 scalar_t__ next_idx (scalar_t__,struct vio_dring_state*) ; 
 scalar_t__ prev_idx (scalar_t__,struct vio_dring_state*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int vnet_send_ack (struct vnet_port*,struct vio_dring_state*,int,int,int /*<<< orphan*/ ) ; 
 int vnet_walk_rx_one (struct vnet_port*,struct vio_dring_state*,scalar_t__,int*) ; 

__attribute__((used)) static int vnet_walk_rx(struct vnet_port *port, struct vio_dring_state *dr,
			u32 start, u32 end)
{
	struct vio_driver_state *vio = &port->vio;
	int ack_start = -1, ack_end = -1;

	end = (end == (u32) -1) ? prev_idx(start, dr) : next_idx(end, dr);

	viodbg(DATA, "vnet_walk_rx start[%08x] end[%08x]\n", start, end);

	while (start != end) {
		int ack = 0, err = vnet_walk_rx_one(port, dr, start, &ack);
		if (err == -ECONNRESET)
			return err;
		if (err != 0)
			break;
		if (ack_start == -1)
			ack_start = start;
		ack_end = start;
		start = next_idx(start, dr);
		if (ack && start != end) {
			err = vnet_send_ack(port, dr, ack_start, ack_end,
					    VIO_DRING_ACTIVE);
			if (err == -ECONNRESET)
				return err;
			ack_start = -1;
		}
	}
	if (unlikely(ack_start == -1))
		ack_start = ack_end = prev_idx(start, dr);
	return vnet_send_ack(port, dr, ack_start, ack_end, VIO_DRING_STOPPED);
}