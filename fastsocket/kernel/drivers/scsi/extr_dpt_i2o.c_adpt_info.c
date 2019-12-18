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
struct Scsi_Host {scalar_t__* hostdata; } ;
struct TYPE_2__ {scalar_t__ detail; } ;
typedef  TYPE_1__ adpt_hba ;

/* Variables and functions */

__attribute__((used)) static const char *adpt_info(struct Scsi_Host *host)
{
	adpt_hba* pHba;

	pHba = (adpt_hba *) host->hostdata[0];
	return (char *) (pHba->detail);
}