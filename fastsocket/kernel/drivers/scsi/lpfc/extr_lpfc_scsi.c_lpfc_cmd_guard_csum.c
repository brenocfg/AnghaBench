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
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ LPFC_PG_TYPE_NO_DIF ; 
 scalar_t__ SHOST_DIX_GUARD_IP ; 
 scalar_t__ lpfc_prot_group_type (int /*<<< orphan*/ *,struct scsi_cmnd*) ; 
 scalar_t__ scsi_host_get_guard (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned
lpfc_cmd_guard_csum(struct scsi_cmnd *sc)
{
	if (lpfc_prot_group_type(NULL, sc) == LPFC_PG_TYPE_NO_DIF)
		return 0;
	if (scsi_host_get_guard(sc->device->host) == SHOST_DIX_GUARD_IP)
		return 1;
	return 0;
}