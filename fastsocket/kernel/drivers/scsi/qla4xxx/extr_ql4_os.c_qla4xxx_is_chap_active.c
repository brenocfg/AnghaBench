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
typedef  int /*<<< orphan*/  uint16_t ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __qla4xxx_is_chap_active ; 
 int device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qla4xxx_is_chap_active(struct Scsi_Host *shost,
				  uint16_t chap_tbl_idx)
{
	int ret = 0;

	ret = device_for_each_child(&shost->shost_gendev, &chap_tbl_idx,
				    __qla4xxx_is_chap_active);

	return ret;
}