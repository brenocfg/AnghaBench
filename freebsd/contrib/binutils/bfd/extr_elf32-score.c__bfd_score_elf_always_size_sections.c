#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct score_got_info {int local_gotno; int global_gotno; TYPE_1__* global_gotsym; } ;
struct bfd_link_info {TYPE_2__* input_bfds; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_11__ {TYPE_3__* sections; struct TYPE_11__* link_next; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_12__ {int flags; int size; struct TYPE_12__* next; } ;
typedef  TYPE_3__ asection ;
struct TYPE_13__ {int dynsymcount; TYPE_2__* dynobj; } ;
struct TYPE_10__ {int dynindx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SCORE_ELF_GOT_MAX_SIZE (TYPE_2__*) ; 
 int SCORE_ELF_GOT_SIZE (TYPE_2__*) ; 
 int SCORE_FUNCTION_STUB_SIZE ; 
 int SEC_ALLOC ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_6__* elf_hash_table (struct bfd_link_info*) ; 
 struct score_got_info* score_elf_got_info (TYPE_2__*,TYPE_3__**) ; 
 int /*<<< orphan*/  score_elf_resolve_final_got_entries (struct score_got_info*) ; 
 int /*<<< orphan*/  score_elf_sort_hash_table (struct bfd_link_info*,int) ; 

__attribute__((used)) static bfd_boolean
_bfd_score_elf_always_size_sections (bfd *output_bfd,
				     struct bfd_link_info *info)
{
  bfd *dynobj;
  asection *s;
  struct score_got_info *g;
  int i;
  bfd_size_type loadable_size = 0;
  bfd_size_type local_gotno;
  bfd *sub;

  dynobj = elf_hash_table (info)->dynobj;
  if (dynobj == NULL)
    /* Relocatable links don't have it.  */
    return TRUE;

  g = score_elf_got_info (dynobj, &s);
  if (s == NULL)
    return TRUE;

  /* Calculate the total loadable size of the output.  That will give us the
     maximum number of GOT_PAGE entries required.  */
  for (sub = info->input_bfds; sub; sub = sub->link_next)
    {
      asection *subsection;

      for (subsection = sub->sections;
	   subsection;
	   subsection = subsection->next)
	{
	  if ((subsection->flags & SEC_ALLOC) == 0)
	    continue;
	  loadable_size += ((subsection->size + 0xf)
			    &~ (bfd_size_type) 0xf);
	}
    }

  /* There has to be a global GOT entry for every symbol with
     a dynamic symbol table index of DT_SCORE_GOTSYM or
     higher.  Therefore, it make sense to put those symbols
     that need GOT entries at the end of the symbol table.  We
     do that here.  */
  if (! score_elf_sort_hash_table (info, 1))
    return FALSE;

  if (g->global_gotsym != NULL)
    i = elf_hash_table (info)->dynsymcount - g->global_gotsym->dynindx;
  else
    /* If there are no global symbols, or none requiring
       relocations, then GLOBAL_GOTSYM will be NULL.  */
    i = 0;

  /* In the worst case, we'll get one stub per dynamic symbol.  */
  loadable_size += SCORE_FUNCTION_STUB_SIZE * i;

  /* Assume there are two loadable segments consisting of
     contiguous sections.  Is 5 enough?  */
  local_gotno = (loadable_size >> 16) + 5;

  g->local_gotno += local_gotno;
  s->size += g->local_gotno * SCORE_ELF_GOT_SIZE (output_bfd);

  g->global_gotno = i;
  s->size += i * SCORE_ELF_GOT_SIZE (output_bfd);

  score_elf_resolve_final_got_entries (g);

  if (s->size > SCORE_ELF_GOT_MAX_SIZE (output_bfd))
    {
      /* Fixme. Error message or Warning message should be issued here.  */
    }

  return TRUE;
}