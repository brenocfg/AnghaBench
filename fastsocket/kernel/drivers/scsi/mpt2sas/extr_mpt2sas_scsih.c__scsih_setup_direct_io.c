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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct scsi_cmnd {scalar_t__* cmnd; } ;
struct _raid_device {scalar_t__ block_exponent; scalar_t__ max_lba; scalar_t__ stripe_sz; scalar_t__ stripe_exponent; scalar_t__ num_pds; int /*<<< orphan*/ * pd_handle; } ;
struct MPT2SAS_ADAPTER {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__* CDB32; } ;
struct TYPE_5__ {void* DevHandle; TYPE_1__ CDB; } ;
typedef  TYPE_2__ Mpi2SCSIIORequest_t ;

/* Variables and functions */
 scalar_t__ READ_10 ; 
 scalar_t__ READ_16 ; 
 scalar_t__ WRITE_10 ; 
 scalar_t__ WRITE_16 ; 
 int /*<<< orphan*/  _scsih_scsi_direct_io_set (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 

__attribute__((used)) static void
_scsih_setup_direct_io(struct MPT2SAS_ADAPTER *ioc, struct scsi_cmnd *scmd,
	struct _raid_device *raid_device, Mpi2SCSIIORequest_t *mpi_request,
	u16 smid)
{
	u32 v_lba, p_lba, stripe_off, stripe_unit, column, io_size;
	u32 stripe_sz, stripe_exp;
	u8 num_pds, *cdb_ptr, i;
	u8 cdb0 = scmd->cmnd[0];
	u64 v_llba;

	/*
	 * Try Direct I/O to RAID memeber disks
	 */
	if (cdb0 == READ_16 || cdb0 == READ_10 ||
	    cdb0 == WRITE_16 || cdb0 == WRITE_10) {
		cdb_ptr = mpi_request->CDB.CDB32;

		if ((cdb0 < READ_16) || !(cdb_ptr[2] | cdb_ptr[3] | cdb_ptr[4]
			| cdb_ptr[5])) {
			io_size = scsi_bufflen(scmd) >>
			    raid_device->block_exponent;
			i = (cdb0 < READ_16) ? 2 : 6;
			/* get virtual lba */
			v_lba = be32_to_cpu(*(__be32 *)(&cdb_ptr[i]));

			if (((u64)v_lba + (u64)io_size - 1) <=
			    (u32)raid_device->max_lba) {
				stripe_sz = raid_device->stripe_sz;
				stripe_exp = raid_device->stripe_exponent;
				stripe_off = v_lba & (stripe_sz - 1);

				/* Check whether IO falls within a stripe */
				if ((stripe_off + io_size) <= stripe_sz) {
					num_pds = raid_device->num_pds;
					p_lba = v_lba >> stripe_exp;
					stripe_unit = p_lba / num_pds;
					column = p_lba % num_pds;
					p_lba = (stripe_unit << stripe_exp) +
					    stripe_off;
					mpi_request->DevHandle =
						cpu_to_le16(raid_device->
						    pd_handle[column]);
					(*(__be32 *)(&cdb_ptr[i])) =
						cpu_to_be32(p_lba);
					/*
					* WD: To indicate this I/O is directI/O
					*/
					_scsih_scsi_direct_io_set(ioc, smid, 1);
				}
			}
		} else {
			io_size = scsi_bufflen(scmd) >>
			    raid_device->block_exponent;
			/* get virtual lba */
			v_llba = be64_to_cpu(*(__be64 *)(&cdb_ptr[2]));

			if ((v_llba + (u64)io_size - 1) <=
			    raid_device->max_lba) {
				stripe_sz = raid_device->stripe_sz;
				stripe_exp = raid_device->stripe_exponent;
				stripe_off = (u32) (v_llba & (stripe_sz - 1));

				/* Check whether IO falls within a stripe */
				if ((stripe_off + io_size) <= stripe_sz) {
					num_pds = raid_device->num_pds;
					p_lba = (u32)(v_llba >> stripe_exp);
					stripe_unit = p_lba / num_pds;
					column = p_lba % num_pds;
					p_lba = (stripe_unit << stripe_exp) +
					    stripe_off;
					mpi_request->DevHandle =
						cpu_to_le16(raid_device->
						    pd_handle[column]);
					(*(__be64 *)(&cdb_ptr[2])) =
					    cpu_to_be64((u64)p_lba);
					/*
					* WD: To indicate this I/O is directI/O
					*/
					_scsih_scsi_direct_io_set(ioc, smid, 1);
				}
			}
		}
	}
}