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
struct ipr_ioa_cfg {int hrrq_num; int /*<<< orphan*/  hrrq_index; } ;

/* Variables and functions */
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipr_get_hrrq_index(struct ipr_ioa_cfg *ioa_cfg)
{
	if (ioa_cfg->hrrq_num == 1)
		return 0;
	else
		return (atomic_add_return(1, &ioa_cfg->hrrq_index) % (ioa_cfg->hrrq_num - 1)) + 1;
}