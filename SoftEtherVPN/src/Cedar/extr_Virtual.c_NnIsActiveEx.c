#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* NativeNat; } ;
typedef  TYPE_2__ VH ;
struct TYPE_4__ {scalar_t__ PublicIP; int Active; int IsRawIpMode; } ;

/* Variables and functions */

bool NnIsActiveEx(VH *v, bool *is_ipraw_mode)
{
	// Validate arguments
	if (v == NULL)
	{
		return false;
	}

	if (v->NativeNat == NULL)
	{
		return false;
	}

	if (v->NativeNat->PublicIP == 0)
	{
		return false;
	}

	if (v->NativeNat->Active)
	{
		if (is_ipraw_mode != NULL)
		{
			*is_ipraw_mode = v->NativeNat->IsRawIpMode;
		}
	}

	return v->NativeNat->Active;
}