#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {int /*<<< orphan*/  OptionList; } ;
struct TYPE_9__ {int IsAccepted; int IsSupported; int AltDataSize; int /*<<< orphan*/  AltData; } ;
typedef  TYPE_1__ PPP_OPTION ;
typedef  TYPE_2__ PPP_LCP ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* GetOptionValue (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 int IsZeroIP (int /*<<< orphan*/ *) ; 
 TYPE_1__* NewPPPOption (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ PPPGetIPAddressValueFromLCP (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool PPPSetIPAddressValueToLCP(PPP_LCP *c, UINT type, IP *ip, bool only_modify)
{
	IP ip2;
	UINT ui;
	// Validate arguments
	if (c == NULL || ip == NULL)
	{
		return false;
	}

	ui = IPToUINT(ip);

	if (PPPGetIPAddressValueFromLCP(c, type, &ip2))
	{
		PPP_OPTION *opt;
		opt = GetOptionValue(c, type);

		if (opt != NULL)
		{
			if (IsZeroIP(ip) == false)
			{
				if (CmpIpAddr(&ip2, ip) == 0)
				{
					// No change
					opt->IsAccepted = true;
					opt->IsSupported = true;
				}
				else
				{
					// Changed
					opt->IsAccepted = false;
					opt->IsSupported = true;
					opt->AltDataSize = 4;
					Copy(opt->AltData, &ui, 4);
				}
			}
			else
			{
				// The parameter itself is not supported
				// (if the IP address is 0.0.0.0)
				opt->IsSupported = false;
				opt->IsAccepted = false;
			}
		}

		return true;
	}
	else
	{
		if (IsZeroIP(ip) == false)
		{
			// Add as a new item
			if (only_modify != false)
			{
				return false;
			}
			else
			{
				PPP_OPTION *opt2 = NewPPPOption(type, &ui, 4);
				opt2->IsAccepted = opt2->IsSupported = true;

				Add(c->OptionList, opt2);

				return true;
			}
		}
		else
		{
			return false;
		}
	}
}