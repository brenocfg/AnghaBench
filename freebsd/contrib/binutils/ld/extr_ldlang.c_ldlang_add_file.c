#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lang_statement_union_type ;
struct TYPE_8__ {TYPE_2__* the_bfd; int /*<<< orphan*/  next; } ;
typedef  TYPE_1__ lang_input_statement_type ;
struct TYPE_10__ {TYPE_2__** input_bfds_tail; } ;
struct TYPE_9__ {TYPE_1__* usrdata; struct TYPE_9__* link_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  bfd_map_over_sections (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_set_gp_size (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_chain ; 
 int /*<<< orphan*/  g_switch_value ; 
 int /*<<< orphan*/  lang_statement_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__ link_info ; 
 TYPE_2__* output_bfd ; 
 int /*<<< orphan*/  section_already_linked ; 

void
ldlang_add_file (lang_input_statement_type *entry)
{
  lang_statement_append (&file_chain,
			 (lang_statement_union_type *) entry,
			 &entry->next);

  /* The BFD linker needs to have a list of all input BFDs involved in
     a link.  */
  ASSERT (entry->the_bfd->link_next == NULL);
  ASSERT (entry->the_bfd != output_bfd);

  *link_info.input_bfds_tail = entry->the_bfd;
  link_info.input_bfds_tail = &entry->the_bfd->link_next;
  entry->the_bfd->usrdata = entry;
  bfd_set_gp_size (entry->the_bfd, g_switch_value);

  /* Look through the sections and check for any which should not be
     included in the link.  We need to do this now, so that we can
     notice when the backend linker tries to report multiple
     definition errors for symbols which are in sections we aren't
     going to link.  FIXME: It might be better to entirely ignore
     symbols which are defined in sections which are going to be
     discarded.  This would require modifying the backend linker for
     each backend which might set the SEC_LINK_ONCE flag.  If we do
     this, we should probably handle SEC_EXCLUDE in the same way.  */

  bfd_map_over_sections (entry->the_bfd, section_already_linked, entry);
}