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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int PackGetStr (int /*<<< orphan*/ *,char*,char*,scalar_t__) ; 

bool GetMethodFromPack(PACK *p, char *method, UINT size)
{
	// Validate arguments
	if (p == NULL || method == NULL || size == 0)
	{
		return false;
	}

	return PackGetStr(p, "method", method, size);
}