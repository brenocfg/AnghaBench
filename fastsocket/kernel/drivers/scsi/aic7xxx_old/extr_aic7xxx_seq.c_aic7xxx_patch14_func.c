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
struct aic7xxx_host {int bugs; } ;

/* Variables and functions */
 int AHC_BUG_PCI_2_1_RETRY ; 

__attribute__((used)) static int
aic7xxx_patch14_func(struct aic7xxx_host *p)
{
	return ((p->bugs & AHC_BUG_PCI_2_1_RETRY) != 0);
}