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
struct device_node {int dummy; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  UNI_N_AACK_DELAY ; 
 int /*<<< orphan*/  UNI_N_AACK_DELAY_ENABLE ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 int /*<<< orphan*/  UN_BIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UN_BIS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uninorth_rev ; 

__attribute__((used)) static long
intrepid_aack_delay_enable(struct device_node *node, long param, long value)
{
	unsigned long flags;

	if (uninorth_rev < 0xd2)
		return -ENODEV;

	LOCK(flags);
	if (param)
		UN_BIS(UNI_N_AACK_DELAY, UNI_N_AACK_DELAY_ENABLE);
	else
		UN_BIC(UNI_N_AACK_DELAY, UNI_N_AACK_DELAY_ENABLE);
	UNLOCK(flags);

	return 0;
}