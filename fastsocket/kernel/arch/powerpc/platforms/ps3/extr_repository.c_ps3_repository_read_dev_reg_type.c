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
typedef  int u64 ;
typedef  enum ps3_reg_type { ____Placeholder_ps3_reg_type } ps3_reg_type ;

/* Variables and functions */
 int /*<<< orphan*/  PS3_LPAR_ID_PME ; 
 int /*<<< orphan*/  make_field (char*,unsigned int) ; 
 int /*<<< orphan*/  make_first_field (char*,unsigned int) ; 
 int read_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

int ps3_repository_read_dev_reg_type(unsigned int bus_index,
	unsigned int dev_index, unsigned int reg_index,
	enum ps3_reg_type *reg_type)
{
	int result;
	u64 v1;

	result = read_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("dev", dev_index),
		make_field("reg", reg_index),
		make_field("type", 0),
		&v1, NULL);
	*reg_type = v1;
	return result;
}