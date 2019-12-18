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
struct bfd_section_already_linked_hash_entry {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_section_already_linked_table ; 
 int /*<<< orphan*/  already_linked_newfunc ; 
 int /*<<< orphan*/  bfd_hash_table_init_n (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

bfd_boolean
bfd_section_already_linked_table_init (void)
{
  return bfd_hash_table_init_n (&_bfd_section_already_linked_table,
				already_linked_newfunc,
				sizeof (struct bfd_section_already_linked_hash_entry),
				42);
}