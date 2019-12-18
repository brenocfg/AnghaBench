#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* htab_t ;
struct TYPE_4__ {scalar_t__* entries; int /*<<< orphan*/  n_deleted; int /*<<< orphan*/  (* del_f ) (scalar_t__) ;} ;
typedef  scalar_t__ PTR ;

/* Variables and functions */
 scalar_t__ HTAB_DELETED_ENTRY ; 
 scalar_t__ HTAB_EMPTY_ENTRY ; 
 int /*<<< orphan*/  abort () ; 
 int htab_size (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void
htab_clear_slot (htab_t htab, PTR *slot)
{
  if (slot < htab->entries || slot >= htab->entries + htab_size (htab)
      || *slot == HTAB_EMPTY_ENTRY || *slot == HTAB_DELETED_ENTRY)
    abort ();

  if (htab->del_f)
    (*htab->del_f) (*slot);

  *slot = HTAB_DELETED_ENTRY;
  htab->n_deleted++;
}