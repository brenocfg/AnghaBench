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
struct restore_data_record {scalar_t__ magic; int /*<<< orphan*/  cr3; int /*<<< orphan*/  jump_address; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RESTORE_MAGIC ; 
 int /*<<< orphan*/  restore_cr3 ; 
 int /*<<< orphan*/  restore_jump_address ; 

int arch_hibernation_header_restore(void *addr)
{
	struct restore_data_record *rdr = addr;

	restore_jump_address = rdr->jump_address;
	restore_cr3 = rdr->cr3;
	return (rdr->magic == RESTORE_MAGIC) ? 0 : -EINVAL;
}