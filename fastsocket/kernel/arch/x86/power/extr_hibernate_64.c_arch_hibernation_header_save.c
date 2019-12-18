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
struct restore_data_record {int /*<<< orphan*/  magic; int /*<<< orphan*/  cr3; int /*<<< orphan*/  jump_address; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int /*<<< orphan*/  RESTORE_MAGIC ; 
 int /*<<< orphan*/  restore_cr3 ; 
 int /*<<< orphan*/  restore_jump_address ; 

int arch_hibernation_header_save(void *addr, unsigned int max_size)
{
	struct restore_data_record *rdr = addr;

	if (max_size < sizeof(struct restore_data_record))
		return -EOVERFLOW;
	rdr->jump_address = restore_jump_address;
	rdr->cr3 = restore_cr3;
	rdr->magic = RESTORE_MAGIC;
	return 0;
}