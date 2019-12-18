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
struct inet_port {int /*<<< orphan*/  row_status; int /*<<< orphan*/  tport; } ;
typedef  enum RowStatus { ____Placeholder_RowStatus } RowStatus ;
struct TYPE_2__ {void* int1; } ;

/* Variables and functions */
#define  RowStatus_active 133 
#define  RowStatus_createAndGo 132 
#define  RowStatus_createAndWait 131 
#define  RowStatus_destroy 130 
#define  RowStatus_notInService 129 
#define  RowStatus_notReady 128 
 void* SET_ACTIVATED ; 
 void* SET_CREATED ; 
 void* SET_DEACTIVATE ; 
 void* SET_DESTROY ; 
 int SNMP_ERR_INCONS_VALUE ; 
 int SNMP_ERR_NOERROR ; 
 int SNMP_ERR_WRONG_VALUE ; 
 int /*<<< orphan*/  abort () ; 
 int create_and_go (struct snmp_context*,struct inet_port_params*) ; 
 int create_and_wait (struct snmp_context*,struct inet_port_params*) ; 
 int inet_activate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
inet_port_set(struct snmp_context *ctx, struct inet_port *port,
    struct inet_port_params *params, enum RowStatus nstatus)
{
	switch (nstatus) {

	  case RowStatus_createAndGo:
		if (port != NULL)
			return (SNMP_ERR_INCONS_VALUE);
		ctx->scratch->int1 = SET_CREATED;
		return (create_and_go(ctx, params));

	  case RowStatus_createAndWait:
		if (port != NULL)
			return (SNMP_ERR_INCONS_VALUE);
		ctx->scratch->int1 = SET_CREATED;
		return (create_and_wait(ctx, params));

	  case RowStatus_active:
		if (port == NULL)
			return (SNMP_ERR_INCONS_VALUE);

		switch (port->row_status) {

		  case RowStatus_notReady:
			/* this can not happend */
			abort();

		  case RowStatus_notInService:
			ctx->scratch->int1 = SET_ACTIVATED;
			return (inet_activate(&port->tport));

		  case RowStatus_active:
			return (SNMP_ERR_NOERROR);

		  case RowStatus_createAndGo:
		  case RowStatus_createAndWait:
		  case RowStatus_destroy:
			abort();
		}
		break;

	  case RowStatus_notInService:
		if (port == NULL)
			return (SNMP_ERR_INCONS_VALUE);

		switch (port->row_status) {

		  case RowStatus_notReady:
			/* this can not happend */
			abort();

		  case RowStatus_notInService:
			return (SNMP_ERR_NOERROR);

		  case RowStatus_active:
			/* this is done during commit */
			ctx->scratch->int1 = SET_DEACTIVATE;
			return (SNMP_ERR_NOERROR);

		  case RowStatus_createAndGo:
		  case RowStatus_createAndWait:
		  case RowStatus_destroy:
			abort();
		}
		break;
		
	  case RowStatus_destroy:
		/* this is done during commit */
		ctx->scratch->int1 = SET_DESTROY;
		return (SNMP_ERR_NOERROR);

	  case RowStatus_notReady:
		return (SNMP_ERR_WRONG_VALUE);
	}
	abort();
}