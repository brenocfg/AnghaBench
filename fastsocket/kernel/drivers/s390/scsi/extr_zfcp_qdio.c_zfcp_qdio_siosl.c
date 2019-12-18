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
struct zfcp_adapter {int /*<<< orphan*/  status; int /*<<< orphan*/  ccw_device; } ;

/* Variables and functions */
 int ZFCP_STATUS_ADAPTER_SIOSL_ISSUED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set_mask (int,int /*<<< orphan*/ *) ; 
 int ccw_device_siosl (int /*<<< orphan*/ ) ; 

void zfcp_qdio_siosl(struct zfcp_adapter *adapter)
{
	int rc;

	if (atomic_read(&adapter->status) & ZFCP_STATUS_ADAPTER_SIOSL_ISSUED)
		return;

	rc = ccw_device_siosl(adapter->ccw_device);
	if (!rc)
		atomic_set_mask(ZFCP_STATUS_ADAPTER_SIOSL_ISSUED,
				&adapter->status);
}