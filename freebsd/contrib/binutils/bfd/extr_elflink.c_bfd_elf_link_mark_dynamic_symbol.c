#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  string; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ root; } ;
struct elf_link_hash_entry {int dynamic; scalar_t__ type; TYPE_2__ root; } ;
struct bfd_link_info {scalar_t__ dynamic_data; scalar_t__ relocatable; struct bfd_elf_dynamic_list* dynamic_list; } ;
struct bfd_elf_dynamic_list {int /*<<< orphan*/  head; scalar_t__ (* match ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  st_info; } ;
typedef  TYPE_3__ Elf_Internal_Sym ;

/* Variables and functions */
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ STT_OBJECT ; 
 scalar_t__ bfd_link_hash_new ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
bfd_elf_link_mark_dynamic_symbol (struct bfd_link_info *info,
				  struct elf_link_hash_entry *h,
				  Elf_Internal_Sym *sym)
{
  struct bfd_elf_dynamic_list *d = info->dynamic_list;

  /* It may be called more than once on the same H.  */
  if(h->dynamic || info->relocatable)
    return;

  if ((info->dynamic_data
       && (h->type == STT_OBJECT
	   || (sym != NULL
	       && ELF_ST_TYPE (sym->st_info) == STT_OBJECT)))
      || (d != NULL 
	  && h->root.type == bfd_link_hash_new
	  && (*d->match) (&d->head, NULL, h->root.root.string)))
    h->dynamic = 1;
}