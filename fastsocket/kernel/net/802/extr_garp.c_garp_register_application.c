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
struct TYPE_2__ {struct garp_application* data; int /*<<< orphan*/  rcv; } ;
struct garp_application {TYPE_1__ proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  garp_pdu_rcv ; 
 int stp_proto_register (TYPE_1__*) ; 

int garp_register_application(struct garp_application *appl)
{
	appl->proto.rcv = garp_pdu_rcv;
	appl->proto.data = appl;
	return stp_proto_register(&appl->proto);
}