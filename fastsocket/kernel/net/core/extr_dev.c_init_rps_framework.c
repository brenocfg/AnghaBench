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
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IPPROTO_MAX ; 
 int /*<<< orphan*/ * rps_table ; 

__attribute__((used)) static void init_rps_framework(void)
{
	int i;

	for (i = 0; i < IPPROTO_MAX; i++)
		INIT_LIST_HEAD(&rps_table[i]);
}