#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  WinsServer2; int /*<<< orphan*/  WinsServer1; int /*<<< orphan*/  DnsServer2; int /*<<< orphan*/  DnsServer1; int /*<<< orphan*/  IpAddress; } ;
typedef  int /*<<< orphan*/  PPP_LCP ;
typedef  TYPE_1__ PPP_IPOPTION ;

/* Variables and functions */
 int PPPGetIPAddressValueFromLCP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PPP_IPCP_OPTION_DNS1 ; 
 int /*<<< orphan*/  PPP_IPCP_OPTION_DNS2 ; 
 int /*<<< orphan*/  PPP_IPCP_OPTION_IP ; 
 int /*<<< orphan*/  PPP_IPCP_OPTION_WINS1 ; 
 int /*<<< orphan*/  PPP_IPCP_OPTION_WINS2 ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

bool PPPGetIPOptionFromLCP(PPP_IPOPTION *o, PPP_LCP *c)
{
	bool ret;
	// Validate arguments
	if (c == NULL || o == NULL)
	{
		return false;
	}

	Zero(o, sizeof(PPP_IPOPTION));

	ret = PPPGetIPAddressValueFromLCP(c, PPP_IPCP_OPTION_IP, &o->IpAddress);

	PPPGetIPAddressValueFromLCP(c, PPP_IPCP_OPTION_DNS1, &o->DnsServer1);
	PPPGetIPAddressValueFromLCP(c, PPP_IPCP_OPTION_DNS2, &o->DnsServer2);
	PPPGetIPAddressValueFromLCP(c, PPP_IPCP_OPTION_WINS1, &o->WinsServer1);
	PPPGetIPAddressValueFromLCP(c, PPP_IPCP_OPTION_WINS2, &o->WinsServer2);

	return ret;
}