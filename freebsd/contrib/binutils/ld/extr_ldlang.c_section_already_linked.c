#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ just_syms_flag; } ;
typedef  TYPE_1__ lang_input_statement_type ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_2__ bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  bfd_link_just_syms (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_section_already_linked (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_info ; 

__attribute__((used)) static void
section_already_linked (bfd *abfd, asection *sec, void *data)
{
  lang_input_statement_type *entry = data;

  /* If we are only reading symbols from this object, then we want to
     discard all sections.  */
  if (entry->just_syms_flag)
    {
      bfd_link_just_syms (abfd, sec, &link_info);
      return;
    }

  if (!(abfd->flags & DYNAMIC))
    bfd_section_already_linked (abfd, sec, &link_info);
}