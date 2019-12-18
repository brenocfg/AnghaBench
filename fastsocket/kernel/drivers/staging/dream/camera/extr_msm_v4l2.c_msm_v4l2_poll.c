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
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* drv; } ;
struct TYPE_3__ {unsigned int (* drv_poll ) (int /*<<< orphan*/ ,struct file*,struct poll_table_struct*) ;int /*<<< orphan*/  sync; } ;

/* Variables and functions */
 TYPE_2__* g_pmsm_v4l2_dev ; 
 unsigned int stub1 (int /*<<< orphan*/ ,struct file*,struct poll_table_struct*) ; 

__attribute__((used)) static unsigned int msm_v4l2_poll(struct file *f, struct poll_table_struct *w)
{
	return g_pmsm_v4l2_dev->drv->drv_poll(g_pmsm_v4l2_dev->drv->sync, f, w);
}