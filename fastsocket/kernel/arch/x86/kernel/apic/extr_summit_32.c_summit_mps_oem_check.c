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
struct mpc_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mark_tsc_unstable (char*) ; 
 int /*<<< orphan*/  setup_summit () ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int use_cyclone ; 

__attribute__((used)) static int summit_mps_oem_check(struct mpc_table *mpc, char *oem,
		char *productid)
{
	if (!strncmp(oem, "IBM ENSW", 8) &&
			(!strncmp(productid, "VIGIL SMP", 9)
			 || !strncmp(productid, "EXA", 3)
			 || !strncmp(productid, "RUTHLESS SMP", 12))){
		mark_tsc_unstable("Summit based system");
		use_cyclone = 1; /*enable cyclone-timer*/
		setup_summit();
		return 1;
	}
	return 0;
}