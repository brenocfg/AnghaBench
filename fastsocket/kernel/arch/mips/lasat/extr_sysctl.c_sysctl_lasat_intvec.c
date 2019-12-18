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
typedef  int /*<<< orphan*/  ctl_table ;

/* Variables and functions */
 int /*<<< orphan*/  lasat_write_eeprom_info () ; 
 int sysctl_intvec (int /*<<< orphan*/ *,void*,size_t*,void*,size_t) ; 

int sysctl_lasat_intvec(ctl_table *table,
		    void *oldval, size_t *oldlenp,
		    void *newval, size_t newlen)
{
	int r;

	r = sysctl_intvec(table, oldval, oldlenp, newval, newlen);
	if (r < 0)
		return r;

	if (newval && newlen)
		lasat_write_eeprom_info();

	return 0;
}