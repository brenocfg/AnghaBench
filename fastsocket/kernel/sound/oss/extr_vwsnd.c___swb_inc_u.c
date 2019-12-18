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
struct TYPE_3__ {int swb_u_idx; int swbuf_size; int swb_u_avail; int swb_i_avail; } ;
typedef  TYPE_1__ vwsnd_port_t ;

/* Variables and functions */

__attribute__((used)) static __inline__ unsigned int __swb_inc_u(vwsnd_port_t *port, int inc)
{
	if (inc) {
		port->swb_u_idx += inc;
		port->swb_u_idx %= port->swbuf_size;
		port->swb_u_avail -= inc;
		port->swb_i_avail += inc;
	}
	return port->swb_u_avail;
}