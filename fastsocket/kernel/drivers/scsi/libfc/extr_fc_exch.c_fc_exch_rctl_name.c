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
 int /*<<< orphan*/  FC_TABLE_SIZE (int /*<<< orphan*/ ) ; 
 char const* fc_exch_name_lookup (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_exch_rctl_names ; 

__attribute__((used)) static const char *fc_exch_rctl_name(unsigned int op)
{
	return fc_exch_name_lookup(op, fc_exch_rctl_names,
				   FC_TABLE_SIZE(fc_exch_rctl_names));
}