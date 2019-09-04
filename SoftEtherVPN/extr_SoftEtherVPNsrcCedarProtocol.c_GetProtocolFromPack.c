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
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_TCP ; 

UINT GetProtocolFromPack(PACK *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return 0;
	}

#if	0
	return PackGetInt(p, "protocol");
#else
	// Limit to the TCP protocol in the current version
	return CONNECTION_TCP;
#endif
}