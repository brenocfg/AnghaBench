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
struct poll_table_struct {int dummy; } ;
struct msm_device {int /*<<< orphan*/  sync; } ;
struct file {struct msm_device* private_data; } ;

/* Variables and functions */
 unsigned int __msm_poll_frame (int /*<<< orphan*/ ,struct file*,struct poll_table_struct*) ; 

__attribute__((used)) static unsigned int msm_poll_frame(struct file *filep,
	struct poll_table_struct *pll_table)
{
	struct msm_device *pmsm = filep->private_data;
	return __msm_poll_frame(pmsm->sync, filep, pll_table);
}