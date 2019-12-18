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
struct pd_unit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_status (struct pd_unit*,int) ; 

__attribute__((used)) static void pd_reset(struct pd_unit *disk)
{				/* called only for MASTER drive */
	write_status(disk, 4);
	udelay(50);
	write_status(disk, 0);
	udelay(250);
}