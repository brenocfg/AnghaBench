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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  H_FREE_VTERM ; 
 int hvcs_convert (long) ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hvcs_free_connection(uint32_t unit_address)
{
	long retval;
	retval = plpar_hcall_norets(H_FREE_VTERM, unit_address);
	return hvcs_convert(retval);
}