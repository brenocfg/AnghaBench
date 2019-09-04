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
struct TYPE_3__ {int /*<<< orphan*/  WinsServer2; int /*<<< orphan*/  WinsServer1; int /*<<< orphan*/  DnsServer2; int /*<<< orphan*/  DnsServer1; int /*<<< orphan*/  IpAddress; } ;
typedef  int /*<<< orphan*/  PPP_LCP ;
typedef  TYPE_1__ PPP_IPOPTION ;

/* Variables and functions */
 int PPPSetIPAddressValueToLCP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PPP_IPCP_OPTION_DNS1 ; 
 int /*<<< orphan*/  PPP_IPCP_OPTION_DNS2 ; 
 int /*<<< orphan*/  PPP_IPCP_OPTION_IP ; 
 int /*<<< orphan*/  PPP_IPCP_OPTION_WINS1 ; 
 int /*<<< orphan*/  PPP_IPCP_OPTION_WINS2 ; 

bool PPPSetIPOptionToLCP(PPP_IPOPTION *o, PPP_LCP *c, bool only_modify)
{
	bool ret = false;
	// Validate arguments
	if (c == NULL || o == NULL)
	{
		return false;
	}

	ret = PPPSetIPAddressValueToLCP(c, PPP_IPCP_OPTION_IP, &o->IpAddress, only_modify);

	PPPSetIPAddressValueToLCP(c, PPP_IPCP_OPTION_DNS1, &o->DnsServer1, only_modify);
	PPPSetIPAddressValueToLCP(c, PPP_IPCP_OPTION_DNS2, &o->DnsServer2, only_modify);
	PPPSetIPAddressValueToLCP(c, PPP_IPCP_OPTION_WINS1, &o->WinsServer1, only_modify);
	PPPSetIPAddressValueToLCP(c, PPP_IPCP_OPTION_WINS2, &o->WinsServer2, only_modify);

	return ret;
}