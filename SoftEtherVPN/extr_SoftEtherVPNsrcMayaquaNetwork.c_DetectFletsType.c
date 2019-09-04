#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */

UINT DetectFletsType()
{
	UINT ret = 0;
	//LIST *o = GetHostIPAddressList();
//	UINT i;

/*
	for (i = 0;i < LIST_NUM(o);i++)
	{
		IP *ip = LIST_DATA(o, i);

		if (IsIP6(ip))
		{
			char ip_str[MAX_SIZE];

			IPToStr(ip_str, sizeof(ip_str), ip);

			if (IsInSameNetwork6ByStr(ip_str, "2001:c90::", "/32"))
			{
				// NTT East B-FLETs
				ret |= FLETS_DETECT_TYPE_EAST_BFLETS_PRIVATE;
			}

			if (IsInSameNetwork6ByStr(ip_str, "2408:200::", "/23"))
			{
				// Wrapping in network of NTT East NGN
				ret |= FLETS_DETECT_TYPE_EAST_NGN_PRIVATE;
			}

			if (IsInSameNetwork6ByStr(ip_str, "2001:a200::", "/23"))
			{
				// Wrapping in network of NTT West NGN
				ret |= FLETS_DETECT_TYPE_WEST_NGN_PRIVATE;
			}
		}
	}

	FreeHostIPAddressList(o);
*/
	return ret;
}