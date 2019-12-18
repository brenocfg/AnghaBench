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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_section_already_linked_table ; 
 scalar_t__ bfd_hash_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct bfd_section_already_linked_hash_entry *
bfd_section_already_linked_table_lookup (const char *name)
{
  return ((struct bfd_section_already_linked_hash_entry *)
	  bfd_hash_lookup (&_bfd_section_already_linked_table, name,
			   TRUE, FALSE));
}