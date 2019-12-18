#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t node; TYPE_2__* card; } ;
typedef  TYPE_3__ port_t ;
typedef  int /*<<< orphan*/  port_status_t ;
struct TYPE_6__ {TYPE_1__* status; } ;
struct TYPE_5__ {int /*<<< orphan*/ * port_status; } ;

/* Variables and functions */

__attribute__((used)) static inline port_status_t* get_status(port_t *port)
{
	return &port->card->status->port_status[port->node];
}