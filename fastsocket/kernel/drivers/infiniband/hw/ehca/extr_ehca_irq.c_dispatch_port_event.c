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
struct TYPE_2__ {int port_num; } ;
struct ib_event {int event; TYPE_1__ element; int /*<<< orphan*/ * device; } ;
struct ehca_shca {int /*<<< orphan*/  ib_device; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  ehca_info (int /*<<< orphan*/ *,char*,int,char const*) ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 

__attribute__((used)) static void dispatch_port_event(struct ehca_shca *shca, int port_num,
				enum ib_event_type type, const char *msg)
{
	struct ib_event event;

	ehca_info(&shca->ib_device, "port %d %s.", port_num, msg);
	event.device = &shca->ib_device;
	event.event = type;
	event.element.port_num = port_num;
	ib_dispatch_event(&event);
}