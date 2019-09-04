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
typedef  scalar_t__ kpc_config_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int WHITELIST_COUNT ; 
 scalar_t__* whitelist ; 

__attribute__((used)) static boolean_t
config_in_whitelist(kpc_config_t cfg)
{
	unsigned int i;

	for (i = 0; i < WHITELIST_COUNT; i++) {
		if (cfg == whitelist[i]) {
			return TRUE;
		}
	}

	return FALSE;
}