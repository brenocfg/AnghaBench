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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  mca_cmci_present ; 
 int /*<<< orphan*/  mca_cpu_init () ; 
 int /*<<< orphan*/  mca_initialized ; 

boolean_t
mca_is_cmci_present(void)
{
	if (!mca_initialized)
		mca_cpu_init();
	return mca_cmci_present;
}