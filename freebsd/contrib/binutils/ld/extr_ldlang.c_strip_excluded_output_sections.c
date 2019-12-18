#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int constraint; void* ignored; int /*<<< orphan*/  section_relative_symbol; TYPE_6__* bfd_section; struct TYPE_18__* next; } ;
typedef  TYPE_5__ lang_output_section_statement_type ;
typedef  int bfd_boolean ;
struct TYPE_17__ {int /*<<< orphan*/ * link_order; } ;
struct TYPE_16__ {int /*<<< orphan*/ * link_order; TYPE_6__* s; } ;
struct TYPE_19__ {scalar_t__ rawsize; int flags; TYPE_4__ map_tail; TYPE_3__ map_head; } ;
typedef  TYPE_6__ asection ;
struct TYPE_14__ {int /*<<< orphan*/  phase; } ;
struct TYPE_22__ {scalar_t__ phase; TYPE_1__ dataseg; } ;
struct TYPE_21__ {TYPE_2__* head; } ;
struct TYPE_20__ {int /*<<< orphan*/  section_count; } ;
struct TYPE_15__ {TYPE_5__ output_section_statement; } ;

/* Variables and functions */
 int FALSE ; 
 int SEC_EXCLUDE ; 
 int SEC_KEEP ; 
 int SEC_LINKER_CREATED ; 
 void* TRUE ; 
 int /*<<< orphan*/  bfd_section_list_remove (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  bfd_section_removed_from_list (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  exp_dataseg_none ; 
 TYPE_9__ expld ; 
 scalar_t__ lang_mark_phase_enum ; 
 TYPE_8__ lang_output_section_statement ; 
 int /*<<< orphan*/  lang_reset_memory_regions () ; 
 int /*<<< orphan*/  one_lang_size_sections_pass (int /*<<< orphan*/ *,int) ; 
 TYPE_7__* output_bfd ; 
 void* stripped_excluded_sections ; 

void
strip_excluded_output_sections (void)
{
  lang_output_section_statement_type *os;

  /* Run lang_size_sections (if not already done).  */
  if (expld.phase != lang_mark_phase_enum)
    {
      expld.phase = lang_mark_phase_enum;
      expld.dataseg.phase = exp_dataseg_none;
      one_lang_size_sections_pass (NULL, FALSE);
      lang_reset_memory_regions ();
    }

  for (os = &lang_output_section_statement.head->output_section_statement;
       os != NULL;
       os = os->next)
    {
      asection *output_section;
      bfd_boolean exclude;

      if (os->constraint == -1)
	continue;

      output_section = os->bfd_section;
      if (output_section == NULL)
	continue;

      exclude = (output_section->rawsize == 0
		 && (output_section->flags & SEC_KEEP) == 0
		 && !bfd_section_removed_from_list (output_bfd,
						    output_section));

      /* Some sections have not yet been sized, notably .gnu.version,
	 .dynsym, .dynstr and .hash.  These all have SEC_LINKER_CREATED
	 input sections, so don't drop output sections that have such
	 input sections unless they are also marked SEC_EXCLUDE.  */
      if (exclude && output_section->map_head.s != NULL)
	{
	  asection *s;

	  for (s = output_section->map_head.s; s != NULL; s = s->map_head.s)
	    if ((s->flags & SEC_LINKER_CREATED) != 0
		&& (s->flags & SEC_EXCLUDE) == 0)
	      {
		exclude = FALSE;
		break;
	      }
	}

      /* TODO: Don't just junk map_head.s, turn them into link_orders.  */
      output_section->map_head.link_order = NULL;
      output_section->map_tail.link_order = NULL;

      if (exclude)
	{
	  /* We don't set bfd_section to NULL since bfd_section of the
	     removed output section statement may still be used.  */
	  if (!os->section_relative_symbol)
	    os->ignored = TRUE;
	  output_section->flags |= SEC_EXCLUDE;
	  bfd_section_list_remove (output_bfd, output_section);
	  output_bfd->section_count--;
	}
    }

  /* Stop future calls to lang_add_section from messing with map_head
     and map_tail link_order fields.  */
  stripped_excluded_sections = TRUE;
}