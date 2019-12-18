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
struct out_section_hash_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_hash_table_init_n (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_section_statement_newfunc ; 
 int /*<<< orphan*/  output_section_statement_table ; 

__attribute__((used)) static void
output_section_statement_table_init (void)
{
  if (!bfd_hash_table_init_n (&output_section_statement_table,
			      output_section_statement_newfunc,
			      sizeof (struct out_section_hash_entry),
			      61))
    einfo (_("%P%F: can not create hash table: %E\n"));
}