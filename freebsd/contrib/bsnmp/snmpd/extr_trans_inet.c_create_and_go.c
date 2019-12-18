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
struct snmp_context {TYPE_1__* scratch; } ;
struct inet_port_params {int dummy; } ;
struct inet_port {int /*<<< orphan*/  tport; int /*<<< orphan*/  row_status; } ;
struct TYPE_2__ {struct inet_port* ptr1; } ;

/* Variables and functions */
 scalar_t__ COMM_INITIALIZE ; 
 int /*<<< orphan*/  RowStatus_createAndGo ; 
 int SNMP_ERR_NOERROR ; 
 scalar_t__ community ; 
 int inet_activate (int /*<<< orphan*/ *) ; 
 int inet_create (struct inet_port_params*,struct inet_port**) ; 

__attribute__((used)) static int
create_and_go(struct snmp_context *ctx, struct inet_port_params *params)
{
	int err;
	struct inet_port *port;

	if ((err = inet_create(params, &port)) != SNMP_ERR_NOERROR)
		return (err);

	port->row_status = RowStatus_createAndGo;
	ctx->scratch->ptr1 = port;

	if (community == COMM_INITIALIZE)
		return (err);

	return (inet_activate(&port->tport));
}