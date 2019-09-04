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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int DataSize; int IsSupported; scalar_t__ Data; } ;
typedef  TYPE_1__ PPP_OPTION ;
typedef  int /*<<< orphan*/  PPP_LCP ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 TYPE_1__* GetOptionValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool PPPGetIPAddressValueFromLCP(PPP_LCP *c, UINT type, IP *ip)
{
	PPP_OPTION *opt;
	UINT ui;
	// Validate arguments
	if (c == NULL || ip == NULL)
	{
		return false;
	}

	opt = GetOptionValue(c, type);
	if (opt == NULL)
	{
		return false;
	}

	if (opt->DataSize != 4)
	{
		return false;
	}

	opt->IsSupported = true;

	ui = *((UINT *)opt->Data);

	UINTToIP(ip, ui);

	return true;
}