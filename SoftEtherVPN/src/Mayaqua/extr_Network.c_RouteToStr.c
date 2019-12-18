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
typedef  int /*<<< orphan*/  gateway_ip ;
typedef  int /*<<< orphan*/  dest_mask ;
typedef  int /*<<< orphan*/  dest_ip ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  PPPConnection; int /*<<< orphan*/  LocalRouting; int /*<<< orphan*/  InterfaceID; int /*<<< orphan*/  OldIfMetric; int /*<<< orphan*/  Metric; int /*<<< orphan*/  GatewayIP; int /*<<< orphan*/  DestMask; int /*<<< orphan*/  DestIP; } ;
typedef  TYPE_1__ ROUTE_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 

void RouteToStr(char *str, UINT str_size, ROUTE_ENTRY *e)
{
	char dest_ip[MAX_PATH];
	char dest_mask[MAX_PATH];
	char gateway_ip[MAX_PATH];
	// Validate arguments
	if (str == NULL || e == NULL)
	{
		return;
	}

	IPToStr(dest_ip, sizeof(dest_ip), &e->DestIP);
	IPToStr(dest_mask, sizeof(dest_mask), &e->DestMask);
	IPToStr(gateway_ip, sizeof(gateway_ip), &e->GatewayIP);

	Format(str, str_size, "%s/%s %s m=%u oif=%u if=%u lo=%u p=%u",
		dest_ip, dest_mask, gateway_ip,
		e->Metric, e->OldIfMetric, e->InterfaceID,
		e->LocalRouting, e->PPPConnection);
}