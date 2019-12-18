#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lang_definedness_hash_entry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bfd_section; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ABS_SECTION_NAME ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* abs_output_section ; 
 int /*<<< orphan*/  bfd_abs_section_ptr ; 
 int /*<<< orphan*/  bfd_hash_table_init_n (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_chain ; 
 int /*<<< orphan*/  first_file ; 
 int /*<<< orphan*/  input_file_chain ; 
 int /*<<< orphan*/  lang_add_input_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lang_definedness_newfunc ; 
 int /*<<< orphan*/  lang_definedness_table ; 
 int /*<<< orphan*/  lang_input_file_is_marker_enum ; 
 int /*<<< orphan*/  lang_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lang_output_section_statement ; 
 TYPE_1__* lang_output_section_statement_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_begin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  output_section_statement_table_init () ; 
 int /*<<< orphan*/  stat_obstack ; 
 int /*<<< orphan*/ * stat_ptr ; 
 int /*<<< orphan*/  statement_list ; 

void
lang_init (void)
{
  obstack_begin (&stat_obstack, 1000);

  stat_ptr = &statement_list;

  output_section_statement_table_init ();

  lang_list_init (stat_ptr);

  lang_list_init (&input_file_chain);
  lang_list_init (&lang_output_section_statement);
  lang_list_init (&file_chain);
  first_file = lang_add_input_file (NULL, lang_input_file_is_marker_enum,
				    NULL);
  abs_output_section =
    lang_output_section_statement_lookup (BFD_ABS_SECTION_NAME);

  abs_output_section->bfd_section = bfd_abs_section_ptr;

  /* The value "3" is ad-hoc, somewhat related to the expected number of
     DEFINED expressions in a linker script.  For most default linker
     scripts, there are none.  Why a hash table then?  Well, it's somewhat
     simpler to re-use working machinery than using a linked list in terms
     of code-complexity here in ld, besides the initialization which just
     looks like other code here.  */
  if (!bfd_hash_table_init_n (&lang_definedness_table,
			      lang_definedness_newfunc,
			      sizeof (struct lang_definedness_hash_entry),
			      3))
    einfo (_("%P%F: can not create hash table: %E\n"));
}