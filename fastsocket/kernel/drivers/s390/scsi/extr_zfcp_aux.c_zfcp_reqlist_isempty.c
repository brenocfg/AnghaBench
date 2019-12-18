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
struct zfcp_adapter {int /*<<< orphan*/ * req_list; } ;

/* Variables and functions */
 unsigned int REQUEST_LIST_SIZE ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

int zfcp_reqlist_isempty(struct zfcp_adapter *adapter)
{
	unsigned int idx;

	for (idx = 0; idx < REQUEST_LIST_SIZE; idx++)
		if (!list_empty(&adapter->req_list[idx]))
			return 0;
	return 1;
}