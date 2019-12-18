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
struct fde_entry {struct cfi_insn_data** last; } ;
struct cfi_insn_data {struct cfi_insn_data* next; } ;
struct TYPE_4__ {TYPE_1__* frch_cfi_data; } ;
struct TYPE_3__ {struct fde_entry* cur_fde_data; } ;

/* Variables and functions */
 TYPE_2__* frchain_now ; 
 struct cfi_insn_data* xcalloc (int,int) ; 

__attribute__((used)) static struct cfi_insn_data *
alloc_cfi_insn_data (void)
{
  struct cfi_insn_data *insn = xcalloc (1, sizeof (struct cfi_insn_data));
  struct fde_entry *cur_fde_data = frchain_now->frch_cfi_data->cur_fde_data;

  *cur_fde_data->last = insn;
  cur_fde_data->last = &insn->next;

  return insn;
}