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
struct zfcp_dbf {struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  erp_counter; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfcp_dbf_rec_target (char*,void*,struct zfcp_dbf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zfcp_dbf_rec_adapter(char *id, void *ref, struct zfcp_dbf *dbf)
{
	struct zfcp_adapter *adapter = dbf->adapter;

	zfcp_dbf_rec_target(id, ref, dbf, &adapter->status,
				  &adapter->erp_counter, 0, 0, 0);
}