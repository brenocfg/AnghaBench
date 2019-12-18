#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct cref_ref {TYPE_7__* abfd; scalar_t__ def; struct cref_ref* next; } ;
struct TYPE_8__ {int /*<<< orphan*/  string; } ;
struct cref_hash_entry {char* demangled; struct cref_ref* refs; TYPE_1__ root; } ;
struct TYPE_11__ {TYPE_3__* section; } ;
struct TYPE_12__ {TYPE_4__ def; } ;
struct bfd_link_hash_entry {scalar_t__ type; TYPE_5__ u; } ;
struct TYPE_14__ {int flags; } ;
struct TYPE_13__ {int /*<<< orphan*/  hash; } ;
struct TYPE_10__ {TYPE_2__* owner; int /*<<< orphan*/ * output_section; } ;
struct TYPE_9__ {int flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DYNAMIC ; 
 int /*<<< orphan*/  FALSE ; 
 int FILECOL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_link_hash_defined ; 
 struct bfd_link_hash_entry* bfd_link_hash_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  einfo (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  lfinfo (int /*<<< orphan*/ *,char*,TYPE_7__*) ; 
 TYPE_6__ link_info ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
output_one_cref (FILE *fp, struct cref_hash_entry *h)
{
  int len;
  struct bfd_link_hash_entry *hl;
  struct cref_ref *r;

  hl = bfd_link_hash_lookup (link_info.hash, h->root.string, FALSE,
			     FALSE, TRUE);
  if (hl == NULL)
    einfo ("%P: symbol `%T' missing from main hash table\n",
	   h->root.string);
  else
    {
      /* If this symbol is defined in a dynamic object but never
	 referenced by a normal object, then don't print it.  */
      if (hl->type == bfd_link_hash_defined)
	{
	  if (hl->u.def.section->output_section == NULL)
	    return;
	  if (hl->u.def.section->owner != NULL
	      && (hl->u.def.section->owner->flags & DYNAMIC) != 0)
	    {
	      for (r = h->refs; r != NULL; r = r->next)
		if ((r->abfd->flags & DYNAMIC) == 0)
		  break;
	      if (r == NULL)
		return;
	    }
	}
    }

  fprintf (fp, "%s ", h->demangled);
  len = strlen (h->demangled) + 1;

  for (r = h->refs; r != NULL; r = r->next)
    {
      if (r->def)
	{
	  while (len < FILECOL)
	    {
	      putc (' ', fp);
	      ++len;
	    }
	  lfinfo (fp, "%B\n", r->abfd);
	  len = 0;
	}
    }

  for (r = h->refs; r != NULL; r = r->next)
    {
      if (! r->def)
	{
	  while (len < FILECOL)
	    {
	      putc (' ', fp);
	      ++len;
	    }
	  lfinfo (fp, "%B\n", r->abfd);
	  len = 0;
	}
    }

  ASSERT (len == 0);
}