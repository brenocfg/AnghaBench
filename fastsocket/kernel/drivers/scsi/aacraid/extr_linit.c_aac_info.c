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
struct aac_dev {size_t cardtype; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 TYPE_1__* aac_drivers ; 

__attribute__((used)) static const char *aac_info(struct Scsi_Host *shost)
{
	struct aac_dev *dev = (struct aac_dev *)shost->hostdata;
	return aac_drivers[dev->cardtype].name;
}