#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ipc_table_size {int dummy; } ;
struct ipc_port_request {int dummy; } ;
struct ipc_entry {int dummy; } ;
typedef  TYPE_1__* ipc_table_size_t ;
struct TYPE_6__ {scalar_t__ its_size; } ;

/* Variables and functions */
 TYPE_1__* ITS_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* ipc_table_entries ; 
 int ipc_table_entries_size ; 
 int /*<<< orphan*/  ipc_table_fill (TYPE_1__*,int,int,int) ; 
 TYPE_1__* ipc_table_requests ; 
 int ipc_table_requests_size ; 
 scalar_t__ kalloc (int) ; 

void
ipc_table_init(void)
{
	ipc_table_entries = (ipc_table_size_t)
		kalloc(sizeof(struct ipc_table_size) *
		       ipc_table_entries_size);
	assert(ipc_table_entries != ITS_NULL);

	ipc_table_fill(ipc_table_entries, ipc_table_entries_size - 1,
		       16, sizeof(struct ipc_entry));

	/* the last two elements should have the same size */

	ipc_table_entries[ipc_table_entries_size - 1].its_size =
		ipc_table_entries[ipc_table_entries_size - 2].its_size;


	ipc_table_requests = (ipc_table_size_t)
		kalloc(sizeof(struct ipc_table_size) *
		       ipc_table_requests_size);
	assert(ipc_table_requests != ITS_NULL);

	ipc_table_fill(ipc_table_requests, ipc_table_requests_size - 1,
		       2, sizeof(struct ipc_port_request));

	/* the last element should have zero size */

	ipc_table_requests[ipc_table_requests_size - 1].its_size = 0;
}