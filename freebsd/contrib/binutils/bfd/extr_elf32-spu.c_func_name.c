#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_7__* sym; TYPE_3__* h; } ;
struct function_info {TYPE_4__ u; TYPE_5__* sec; scalar_t__ global; struct function_info* start; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_13__ {char* name; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_5__ asection ;
struct TYPE_15__ {scalar_t__ st_name; scalar_t__ st_value; } ;
struct TYPE_14__ {int /*<<< orphan*/  symtab_hdr; } ;
struct TYPE_9__ {char const* string; } ;
struct TYPE_10__ {TYPE_1__ root; } ;
struct TYPE_11__ {TYPE_2__ root; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Shdr ;

/* Variables and functions */
 char const* bfd_elf_sym_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*,TYPE_5__*) ; 
 char* bfd_malloc (size_t) ; 
 TYPE_6__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,unsigned long) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static const char *
func_name (struct function_info *fun)
{
  asection *sec;
  bfd *ibfd;
  Elf_Internal_Shdr *symtab_hdr;

  while (fun->start != NULL)
    fun = fun->start;

  if (fun->global)
    return fun->u.h->root.root.string;

  sec = fun->sec;
  if (fun->u.sym->st_name == 0)
    {
      size_t len = strlen (sec->name);
      char *name = bfd_malloc (len + 10);
      if (name == NULL)
	return "(null)";
      sprintf (name, "%s+%lx", sec->name,
	       (unsigned long) fun->u.sym->st_value & 0xffffffff);
      return name;
    }
  ibfd = sec->owner;
  symtab_hdr = &elf_tdata (ibfd)->symtab_hdr;
  return bfd_elf_sym_name (ibfd, symtab_hdr, fun->u.sym, sec);
}