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
struct atm_dev {int /*<<< orphan*/ * phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idt77105_ops ; 

int idt77105_init(struct atm_dev *dev)
{
	dev->phy = &idt77105_ops;
	return 0;
}