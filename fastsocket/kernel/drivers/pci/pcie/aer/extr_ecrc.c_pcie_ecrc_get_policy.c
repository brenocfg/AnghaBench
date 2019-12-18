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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ecrc_policy ; 
 int /*<<< orphan*/ * ecrc_policy_str ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pcie_ecrc_get_policy(char *str)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ecrc_policy_str); i++)
		if (!strncmp(str, ecrc_policy_str[i],
			     strlen(ecrc_policy_str[i])))
			break;
	if (i >= ARRAY_SIZE(ecrc_policy_str))
		return;

	ecrc_policy = i;
}