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
typedef  int UINT ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 scalar_t__ SetSocketBufferSize (scalar_t__,int,int) ; 

UINT SetSocketBufferSizeWithBestEffort(SOCKET s, bool send, UINT size)
{
	// Validate arguments
	if (s == INVALID_SOCKET)
	{
		return 0;
	}

	while (true)
	{
		if (SetSocketBufferSize(s, send, size))
		{
			return size;
		}

		size = (UINT)((double)size / 1.5);

		if (size <= 32767)
		{
			return 0;
		}
	}
}