#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_4__ {int IOCCapabilities; } ;
struct MPT2SAS_ADAPTER {TYPE_2__ iounit_pg1; TYPE_1__ facts; int /*<<< orphan*/  iounit_pg0; int /*<<< orphan*/  ioc_pg8; int /*<<< orphan*/  bios_pg3; int /*<<< orphan*/  bios_pg2; int /*<<< orphan*/  manu_pg10; scalar_t__ ir_firmware; int /*<<< orphan*/  manu_pg0; } ;
typedef  int /*<<< orphan*/  Mpi2ConfigReply_t ;

/* Variables and functions */
 int MPI2_IOCFACTS_CAPABILITY_TASK_SET_FULL_HANDLING ; 
 int /*<<< orphan*/  MPI2_IOUNITPAGE1_DISABLE_TASK_SET_FULL_HANDLING ; 
 int /*<<< orphan*/  _base_display_ioc_capabilities (struct MPT2SAS_ADAPTER*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt2sas_config_get_bios_pg2 (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt2sas_config_get_bios_pg3 (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt2sas_config_get_ioc_pg8 (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt2sas_config_get_iounit_pg0 (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt2sas_config_get_iounit_pg1 (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mpt2sas_config_get_manufacturing_pg0 (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt2sas_config_get_manufacturing_pg10 (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt2sas_config_set_iounit_pg1 (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
_base_static_config_pages(struct MPT2SAS_ADAPTER *ioc)
{
	Mpi2ConfigReply_t mpi_reply;
	u32 iounit_pg1_flags;

	mpt2sas_config_get_manufacturing_pg0(ioc, &mpi_reply, &ioc->manu_pg0);
	if (ioc->ir_firmware)
		mpt2sas_config_get_manufacturing_pg10(ioc, &mpi_reply,
		    &ioc->manu_pg10);
	mpt2sas_config_get_bios_pg2(ioc, &mpi_reply, &ioc->bios_pg2);
	mpt2sas_config_get_bios_pg3(ioc, &mpi_reply, &ioc->bios_pg3);
	mpt2sas_config_get_ioc_pg8(ioc, &mpi_reply, &ioc->ioc_pg8);
	mpt2sas_config_get_iounit_pg0(ioc, &mpi_reply, &ioc->iounit_pg0);
	mpt2sas_config_get_iounit_pg1(ioc, &mpi_reply, &ioc->iounit_pg1);
	_base_display_ioc_capabilities(ioc);

	/*
	 * Enable task_set_full handling in iounit_pg1 when the
	 * facts capabilities indicate that its supported.
	 */
	iounit_pg1_flags = le32_to_cpu(ioc->iounit_pg1.Flags);
	if ((ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_TASK_SET_FULL_HANDLING))
		iounit_pg1_flags &=
		    ~MPI2_IOUNITPAGE1_DISABLE_TASK_SET_FULL_HANDLING;
	else
		iounit_pg1_flags |=
		    MPI2_IOUNITPAGE1_DISABLE_TASK_SET_FULL_HANDLING;
	ioc->iounit_pg1.Flags = cpu_to_le32(iounit_pg1_flags);
	mpt2sas_config_set_iounit_pg1(ioc, &mpi_reply, &ioc->iounit_pg1);

}