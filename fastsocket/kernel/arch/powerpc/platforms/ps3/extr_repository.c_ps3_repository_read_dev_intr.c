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
typedef  void* u64 ;
typedef  enum ps3_interrupt_type { ____Placeholder_ps3_interrupt_type } ps3_interrupt_type ;

/* Variables and functions */
 int /*<<< orphan*/  PS3_LPAR_ID_PME ; 
 int /*<<< orphan*/  make_field (char*,unsigned int) ; 
 int /*<<< orphan*/  make_first_field (char*,unsigned int) ; 
 int read_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,void**) ; 

int ps3_repository_read_dev_intr(unsigned int bus_index,
	unsigned int dev_index, unsigned int intr_index,
	enum ps3_interrupt_type *intr_type, unsigned int *interrupt_id)
{
	int result;
	u64 v1;
	u64 v2;

	result = read_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("dev", dev_index),
		make_field("intr", intr_index),
		0,
		&v1, &v2);
	*intr_type = v1;
	*interrupt_id = v2;
	return result;
}