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
 int /*<<< orphan*/  CONFIG_VFS_NAMES ; 
 int /*<<< orphan*/  M_CACHE ; 
 int /*<<< orphan*/  hashinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_ref_table ; 
 int /*<<< orphan*/  string_table_mask ; 

__attribute__((used)) static void
init_string_table(void)
{
	string_ref_table = hashinit(CONFIG_VFS_NAMES, M_CACHE, &string_table_mask);
}