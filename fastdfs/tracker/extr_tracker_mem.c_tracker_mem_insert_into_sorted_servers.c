#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ FDFSStorageDetail ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tracker_mem_insert_into_sorted_servers( \
		FDFSStorageDetail *pTargetServer,   \
		FDFSStorageDetail **sorted_servers, const int count)
{
	FDFSStorageDetail **ppServer;
	FDFSStorageDetail **ppEnd;

	ppEnd = sorted_servers + count;
	for (ppServer=ppEnd; ppServer>sorted_servers; ppServer--)
	{
		if (strcmp(pTargetServer->id, (*(ppServer-1))->id) > 0)
		{
			break;
		}
		else
		{
			*ppServer = *(ppServer-1);
		}
	}

	*ppServer = pTargetServer;
}