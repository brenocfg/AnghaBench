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
typedef  int /*<<< orphan*/  ctl_table ;
struct TYPE_3__ {int prid; } ;
struct TYPE_4__ {TYPE_1__ li_eeprom_info; } ;

/* Variables and functions */
 TYPE_2__ lasat_board_info ; 
 int /*<<< orphan*/  lasat_init_board_info () ; 
 int /*<<< orphan*/  lasat_write_eeprom_info () ; 
 int sysctl_intvec (int /*<<< orphan*/ *,void*,size_t*,void*,size_t) ; 

__attribute__((used)) static int sysctl_lasat_prid(ctl_table *table,
				     void *oldval, size_t *oldlenp,
				     void *newval, size_t newlen)
{
	int r;

	r = sysctl_intvec(table, oldval, oldlenp, newval, newlen);
	if (r < 0)
		return r;
	if (newval && newlen) {
		lasat_board_info.li_eeprom_info.prid = *(int *)newval;
		lasat_write_eeprom_info();
		lasat_init_board_info();
	}
	return 0;
}