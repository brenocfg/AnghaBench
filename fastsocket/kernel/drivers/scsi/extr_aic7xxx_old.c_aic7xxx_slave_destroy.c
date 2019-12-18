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
struct scsi_device {struct aic_dev_data* hostdata; } ;
struct aic_dev_data {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct aic_dev_data*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
aic7xxx_slave_destroy(struct scsi_device *SDptr)
{
  struct aic_dev_data *aic_dev = SDptr->hostdata;

  list_del(&aic_dev->list);
  SDptr->hostdata = NULL;
  kfree(aic_dev);
  return;
}