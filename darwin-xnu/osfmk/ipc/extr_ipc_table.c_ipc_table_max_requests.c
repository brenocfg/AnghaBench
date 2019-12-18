#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ its_size; } ;

/* Variables and functions */
 TYPE_1__* ipc_table_requests ; 
 int ipc_table_requests_size ; 

unsigned int
ipc_table_max_requests(void)
{
	if (!ipc_table_requests || ipc_table_requests_size < 2)
		return 0;
	return (unsigned int)ipc_table_requests[ipc_table_requests_size - 2].its_size;
}