#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct MPT2SAS_ADAPTER {int /*<<< orphan*/  scsi_lookup_lock; TYPE_1__* chip; } ;
struct TYPE_5__ {scalar_t__ DescriptorTypeDependent; scalar_t__ LMID; int /*<<< orphan*/  SMID; int /*<<< orphan*/  MSIxIndex; int /*<<< orphan*/  RequestFlags; } ;
struct TYPE_6__ {TYPE_2__ Default; } ;
struct TYPE_4__ {int /*<<< orphan*/  RequestDescriptorPostLow; } ;
typedef  TYPE_3__ Mpi2RequestDescriptorUnion_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_REQ_DESCRIPT_FLAGS_DEFAULT_TYPE ; 
 int /*<<< orphan*/  _base_get_msix_index (struct MPT2SAS_ADAPTER*) ; 
 int /*<<< orphan*/  _base_writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

void
mpt2sas_base_put_smid_default(struct MPT2SAS_ADAPTER *ioc, u16 smid)
{
	Mpi2RequestDescriptorUnion_t descriptor;
	u64 *request = (u64 *)&descriptor;

	descriptor.Default.RequestFlags = MPI2_REQ_DESCRIPT_FLAGS_DEFAULT_TYPE;
	descriptor.Default.MSIxIndex =  _base_get_msix_index(ioc);
	descriptor.Default.SMID = cpu_to_le16(smid);
	descriptor.Default.LMID = 0;
	descriptor.Default.DescriptorTypeDependent = 0;
	_base_writeq(*request, &ioc->chip->RequestDescriptorPostLow,
	    &ioc->scsi_lookup_lock);
}