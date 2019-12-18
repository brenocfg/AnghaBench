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
struct lang_phdr {char const* name; struct lang_phdr* next; int /*<<< orphan*/ * flags; int /*<<< orphan*/ * at; void* phdrs; void* filehdr; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  etree_type ;
typedef  void* bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  exp_get_value_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct lang_phdr* lang_phdr_list ; 
 struct lang_phdr* stat_alloc (int) ; 

void
lang_new_phdr (const char *name,
	       etree_type *type,
	       bfd_boolean filehdr,
	       bfd_boolean phdrs,
	       etree_type *at,
	       etree_type *flags)
{
  struct lang_phdr *n, **pp;

  n = stat_alloc (sizeof (struct lang_phdr));
  n->next = NULL;
  n->name = name;
  n->type = exp_get_value_int (type, 0, "program header type");
  n->filehdr = filehdr;
  n->phdrs = phdrs;
  n->at = at;
  n->flags = flags;

  for (pp = &lang_phdr_list; *pp != NULL; pp = &(*pp)->next)
    ;
  *pp = n;
}