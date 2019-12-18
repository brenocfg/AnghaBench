#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ refcount; int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {scalar_t__ link; } ;
struct TYPE_6__ {TYPE_1__ i; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {TYPE_4__ got; TYPE_3__ root; } ;
struct alloc_got_off_arg {scalar_t__ got_elt_size; int /*<<< orphan*/  gotoff; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_link_hash_warning ; 

__attribute__((used)) static bfd_boolean
elf_gc_allocate_got_offsets (struct elf_link_hash_entry *h, void *arg)
{
  struct alloc_got_off_arg *gofarg = arg;

  if (h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  if (h->got.refcount > 0)
    {
      h->got.offset = gofarg->gotoff;
      gofarg->gotoff += gofarg->got_elt_size;
    }
  else
    h->got.offset = (bfd_vma) -1;

  return TRUE;
}