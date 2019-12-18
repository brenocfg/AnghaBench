#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct MPT2SAS_ADAPTER {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  WWID; } ;
typedef  TYPE_1__ Mpi2RaidVolPage1_t ;
typedef  int /*<<< orphan*/  Mpi2ConfigReply_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_RAID_VOLUME_PGAD_FORM_HANDLE ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt2sas_config_get_raid_volume_pg1 (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mpt2sas_config_get_volume_wwid(struct MPT2SAS_ADAPTER *ioc, u16 volume_handle,
    u64 *wwid)
{
	Mpi2ConfigReply_t mpi_reply;
	Mpi2RaidVolPage1_t raid_vol_pg1;

	*wwid = 0;
	if (!(mpt2sas_config_get_raid_volume_pg1(ioc, &mpi_reply,
	    &raid_vol_pg1, MPI2_RAID_VOLUME_PGAD_FORM_HANDLE,
	    volume_handle))) {
		*wwid = le64_to_cpu(raid_vol_pg1.WWID);
		return 0;
	} else
		return -1;
}