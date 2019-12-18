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
struct powertec_info {int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  fas216_intr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t powertecscsi_intr(int irq, void *dev_id)
{
	struct powertec_info *info = dev_id;

	return fas216_intr(&info->info);
}