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

/* Variables and functions */
 int ISDN_MAX_CHANNELS ; 
 int /*<<< orphan*/ * ippp_table ; 
 int /*<<< orphan*/  isdn_ppp_bundle_arr ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void
isdn_ppp_cleanup(void)
{
	int i;

	for (i = 0; i < ISDN_MAX_CHANNELS; i++)
		kfree(ippp_table[i]);

#ifdef CONFIG_ISDN_MPP
	kfree(isdn_ppp_bundle_arr);
#endif /* CONFIG_ISDN_MPP */

}