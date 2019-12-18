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
struct device {int dummy; } ;

/* Variables and functions */
 int LUB_MISC_RD ; 

__attribute__((used)) static int lubbock_mci_get_ro(struct device *dev)
{
	return (LUB_MISC_RD & (1 << 2)) != 0;
}