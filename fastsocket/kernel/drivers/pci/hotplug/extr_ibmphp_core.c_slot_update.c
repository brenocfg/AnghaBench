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
struct slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ALLSTAT ; 
 int get_cur_bus_info (struct slot**) ; 
 int ibmphp_hpc_readslot (struct slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_flag ; 

__attribute__((used)) static inline int slot_update(struct slot **sl)
{
	int rc;
 	rc = ibmphp_hpc_readslot(*sl, READ_ALLSTAT, NULL);
	if (rc) 
		return rc;
	if (!init_flag)
		rc = get_cur_bus_info(sl);
	return rc;
}