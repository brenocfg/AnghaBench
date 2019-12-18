#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct TYPE_4__ {TYPE_1__* ring; } ;
struct lpfc_hba {TYPE_2__ sli; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int txcmplq_max; } ;

/* Variables and functions */
 size_t LPFC_ELS_RING ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t
lpfc_txcmplq_hw_show(struct device *dev, struct device_attribute *attr,
 char *buf)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_hba   *phba = ((struct lpfc_vport *) shost->hostdata)->phba;

	return snprintf(buf, PAGE_SIZE, "%d\n",
		phba->sli.ring[LPFC_ELS_RING].txcmplq_max);
}