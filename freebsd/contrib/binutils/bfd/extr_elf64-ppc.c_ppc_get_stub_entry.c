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
struct ppc_stub_hash_entry {TYPE_3__ const* id_sec; struct ppc_link_hash_entry* h; } ;
struct ppc_link_hash_table {int /*<<< orphan*/  stub_hash_table; TYPE_1__* stub_group; } ;
struct TYPE_9__ {struct ppc_stub_hash_entry* stub_cache; } ;
struct ppc_link_hash_entry {TYPE_2__ u; } ;
struct TYPE_10__ {size_t id; } ;
typedef  TYPE_3__ asection ;
struct TYPE_8__ {TYPE_3__* link_sec; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  free (char*) ; 
 struct ppc_stub_hash_entry* ppc_stub_hash_lookup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ppc_stub_name (TYPE_3__ const*,TYPE_3__ const*,struct ppc_link_hash_entry*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static struct ppc_stub_hash_entry *
ppc_get_stub_entry (const asection *input_section,
		    const asection *sym_sec,
		    struct ppc_link_hash_entry *h,
		    const Elf_Internal_Rela *rel,
		    struct ppc_link_hash_table *htab)
{
  struct ppc_stub_hash_entry *stub_entry;
  const asection *id_sec;

  /* If this input section is part of a group of sections sharing one
     stub section, then use the id of the first section in the group.
     Stub names need to include a section id, as there may well be
     more than one stub used to reach say, printf, and we need to
     distinguish between them.  */
  id_sec = htab->stub_group[input_section->id].link_sec;

  if (h != NULL && h->u.stub_cache != NULL
      && h->u.stub_cache->h == h
      && h->u.stub_cache->id_sec == id_sec)
    {
      stub_entry = h->u.stub_cache;
    }
  else
    {
      char *stub_name;

      stub_name = ppc_stub_name (id_sec, sym_sec, h, rel);
      if (stub_name == NULL)
	return NULL;

      stub_entry = ppc_stub_hash_lookup (&htab->stub_hash_table,
					 stub_name, FALSE, FALSE);
      if (h != NULL)
	h->u.stub_cache = stub_entry;

      free (stub_name);
    }

  return stub_entry;
}