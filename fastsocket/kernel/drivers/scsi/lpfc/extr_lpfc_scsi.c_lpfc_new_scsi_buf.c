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
struct lpfc_vport {TYPE_1__* phba; } ;
struct TYPE_2__ {int (* lpfc_new_scsi_buf ) (struct lpfc_vport*,int) ;} ;

/* Variables and functions */
 int stub1 (struct lpfc_vport*,int) ; 

__attribute__((used)) static inline int
lpfc_new_scsi_buf(struct lpfc_vport *vport, int num_to_alloc)
{
	return vport->phba->lpfc_new_scsi_buf(vport, num_to_alloc);
}