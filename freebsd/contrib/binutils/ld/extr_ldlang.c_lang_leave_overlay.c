#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct overlay_list {struct overlay_list* next; TYPE_1__* os; } ;
typedef  int /*<<< orphan*/  lang_output_section_phdr_list ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ lang_nocrossref_type ;
typedef  int /*<<< orphan*/  lang_memory_region_type ;
typedef  int /*<<< orphan*/  fill_type ;
typedef  int /*<<< orphan*/  etree_type ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * phdrs; int /*<<< orphan*/  sectype; int /*<<< orphan*/ * load_base; int /*<<< orphan*/ * lma_region; int /*<<< orphan*/ * region; int /*<<< orphan*/ * fill; int /*<<< orphan*/  update_dot_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  exp_assop (char,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exp_binop (char,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct overlay_list*) ; 
 int /*<<< orphan*/  lang_add_nocrossref (TYPE_2__*) ; 
 int /*<<< orphan*/  lang_get_regions (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normal_section ; 
 struct overlay_list* overlay_list ; 
 int /*<<< orphan*/ * overlay_max ; 
 int /*<<< orphan*/ * overlay_vma ; 
 TYPE_2__* xmalloc (int) ; 

void
lang_leave_overlay (etree_type *lma_expr,
		    int nocrossrefs,
		    fill_type *fill,
		    const char *memspec,
		    lang_output_section_phdr_list *phdrs,
		    const char *lma_memspec)
{
  lang_memory_region_type *region;
  lang_memory_region_type *lma_region;
  struct overlay_list *l;
  lang_nocrossref_type *nocrossref;

  lang_get_regions (&region, &lma_region,
		    memspec, lma_memspec,
		    lma_expr != NULL, FALSE);

  nocrossref = NULL;

  /* After setting the size of the last section, set '.' to end of the
     overlay region.  */
  if (overlay_list != NULL)
    overlay_list->os->update_dot_tree
      = exp_assop ('=', ".", exp_binop ('+', overlay_vma, overlay_max));

  l = overlay_list;
  while (l != NULL)
    {
      struct overlay_list *next;

      if (fill != NULL && l->os->fill == NULL)
	l->os->fill = fill;

      l->os->region = region;
      l->os->lma_region = lma_region;

      /* The first section has the load address specified in the
	 OVERLAY statement.  The rest are worked out from that.
	 The base address is not needed (and should be null) if
	 an LMA region was specified.  */
      if (l->next == 0)
	{
	  l->os->load_base = lma_expr;
	  l->os->sectype = normal_section;
	}
      if (phdrs != NULL && l->os->phdrs == NULL)
	l->os->phdrs = phdrs;

      if (nocrossrefs)
	{
	  lang_nocrossref_type *nc;

	  nc = xmalloc (sizeof *nc);
	  nc->name = l->os->name;
	  nc->next = nocrossref;
	  nocrossref = nc;
	}

      next = l->next;
      free (l);
      l = next;
    }

  if (nocrossref != NULL)
    lang_add_nocrossref (nocrossref);

  overlay_vma = NULL;
  overlay_list = NULL;
  overlay_max = NULL;
}