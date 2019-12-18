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
struct cfa_save_data {struct cfa_save_data* next; int /*<<< orphan*/  cfa_offset; } ;
struct TYPE_4__ {TYPE_1__* frch_cfi_data; } ;
struct TYPE_3__ {struct cfa_save_data* cfa_save_stack; int /*<<< orphan*/  cur_cfa_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_CFA_remember_state ; 
 int /*<<< orphan*/  cfi_add_CFA_insn (int /*<<< orphan*/ ) ; 
 TYPE_2__* frchain_now ; 
 struct cfa_save_data* xmalloc (int) ; 

void
cfi_add_CFA_remember_state (void)
{
  struct cfa_save_data *p;

  cfi_add_CFA_insn (DW_CFA_remember_state);

  p = xmalloc (sizeof (*p));
  p->cfa_offset = frchain_now->frch_cfi_data->cur_cfa_offset;
  p->next = frchain_now->frch_cfi_data->cfa_save_stack;
  frchain_now->frch_cfi_data->cfa_save_stack = p;
}