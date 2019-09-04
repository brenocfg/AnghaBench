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
typedef  scalar_t__ UINT64 ;

/* Variables and functions */
 scalar_t__ GetDynValue (char*) ; 

UINT64 GetDynValueOrDefault(char *name, UINT64 default_value, UINT64 min_value, UINT64 max_value)
{
	UINT64 ret = GetDynValue(name);

	if (ret == 0)
	{
		return default_value;
	}

	if (ret < min_value)
	{
		ret = min_value;
	}

	if (ret > max_value)
	{
		ret = max_value;
	}

	return ret;
}