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
typedef  int /*<<< orphan*/  NET_BUFFER_LIST_STATUS ;
typedef  int /*<<< orphan*/  NET_BUFFER_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  NET_BUFFER_LIST_NEXT_NBL (int /*<<< orphan*/ ) ; 

void NeoNdisSetNetBufferListsStatus(NET_BUFFER_LIST *nbl, UINT status)
{
	if (nbl == NULL)
	{
		return;
	}

	while (nbl != NULL)
	{
		NET_BUFFER_LIST_STATUS(nbl) = status;

		nbl = NET_BUFFER_LIST_NEXT_NBL(nbl);
	}
}