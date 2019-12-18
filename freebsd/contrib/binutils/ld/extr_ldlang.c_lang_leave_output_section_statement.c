#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lang_output_section_phdr_list ;
typedef  int /*<<< orphan*/  fill_type ;
struct TYPE_2__ {int /*<<< orphan*/ * phdrs; int /*<<< orphan*/ * fill; int /*<<< orphan*/ * addr_tree; int /*<<< orphan*/ * load_base; int /*<<< orphan*/  lma_region; int /*<<< orphan*/  region; } ;

/* Variables and functions */
 TYPE_1__* current_section ; 
 int /*<<< orphan*/  lang_get_regions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stat_ptr ; 
 int /*<<< orphan*/  statement_list ; 

void
lang_leave_output_section_statement (fill_type *fill, const char *memspec,
				     lang_output_section_phdr_list *phdrs,
				     const char *lma_memspec)
{
  lang_get_regions (&current_section->region,
		    &current_section->lma_region,
		    memspec, lma_memspec,
		    current_section->load_base != NULL,
		    current_section->addr_tree != NULL);
  current_section->fill = fill;
  current_section->phdrs = phdrs;
  stat_ptr = &statement_list;
}