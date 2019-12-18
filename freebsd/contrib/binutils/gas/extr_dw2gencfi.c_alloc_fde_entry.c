#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct frch_cfi_data {int dummy; } ;
struct fde_entry {void* lsda_encoding; void* per_encoding; int /*<<< orphan*/  return_column; int /*<<< orphan*/  data; int /*<<< orphan*/ * last; struct fde_entry* next; } ;
struct TYPE_4__ {TYPE_1__* frch_cfi_data; } ;
struct TYPE_3__ {struct fde_entry* cur_fde_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF2_DEFAULT_RETURN_COLUMN ; 
 void* DW_EH_PE_omit ; 
 TYPE_2__* frchain_now ; 
 struct fde_entry** last_fde_data ; 
 void* xcalloc (int,int) ; 

__attribute__((used)) static struct fde_entry *
alloc_fde_entry (void)
{
  struct fde_entry *fde = xcalloc (1, sizeof (struct fde_entry));

  frchain_now->frch_cfi_data = xcalloc (1, sizeof (struct frch_cfi_data));
  frchain_now->frch_cfi_data->cur_fde_data = fde;
  *last_fde_data = fde;
  last_fde_data = &fde->next;

  fde->last = &fde->data;
  fde->return_column = DWARF2_DEFAULT_RETURN_COLUMN;
  fde->per_encoding = DW_EH_PE_omit;
  fde->lsda_encoding = DW_EH_PE_omit;

  return fde;
}