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
struct pmcraid_instance {int /*<<< orphan*/  aen_queue; } ;
struct inode {int dummy; } ;
struct file {struct pmcraid_instance* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fasync_helper (int,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pmcraid_chr_release(struct inode *inode, struct file *filep)
{
	struct pmcraid_instance *pinstance = filep->private_data;

	filep->private_data = NULL;
	fasync_helper(-1, filep, 0, &pinstance->aen_queue);

	return 0;
}