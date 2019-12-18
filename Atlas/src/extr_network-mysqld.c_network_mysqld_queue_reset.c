#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  packet_id_is_reset; } ;
typedef  TYPE_1__ network_socket ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

int network_mysqld_queue_reset(network_socket *sock) {
	sock->packet_id_is_reset = TRUE;

	return 0;
}