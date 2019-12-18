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
struct TYPE_2__ {int max_ddbs; } ;
struct asd_ha_struct {TYPE_1__ hw_prof; } ;
struct asd_ddb_ssp_smp_target_port {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FIND_FREE_DDB (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  SET_DDB (int,struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_ddbsite_write_dword (struct asd_ha_struct*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asd_get_ddb(struct asd_ha_struct *asd_ha)
{
	int ddb, i;

	ddb = FIND_FREE_DDB(asd_ha);
	if (ddb >= asd_ha->hw_prof.max_ddbs) {
		ddb = -ENOMEM;
		goto out;
	}
	SET_DDB(ddb, asd_ha);

	for (i = 0; i < sizeof(struct asd_ddb_ssp_smp_target_port); i+= 4)
		asd_ddbsite_write_dword(asd_ha, ddb, i, 0);
out:
	return ddb;
}