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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {scalar_t__* KeySizes; } ;
typedef  TYPE_1__ IKE_CRYPTO ;

/* Variables and functions */

bool IkeCheckKeySize(IKE_CRYPTO *c, UINT size)
{
	bool ok = false;
	UINT i;
	// Validate arguments
	if (c == NULL || size == 0)
	{
		return false;
	}

	for (i = 0;i < sizeof(c->KeySizes) / sizeof(UINT);i++)
	{
		if (c->KeySizes[i] == size)
		{
			ok = true;
			break;
		}
	}

	return ok;
}