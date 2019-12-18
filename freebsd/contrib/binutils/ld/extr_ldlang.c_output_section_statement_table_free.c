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
 int /*<<< orphan*/  bfd_hash_table_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_section_statement_table ; 

__attribute__((used)) static void
output_section_statement_table_free (void)
{
  bfd_hash_table_free (&output_section_statement_table);
}