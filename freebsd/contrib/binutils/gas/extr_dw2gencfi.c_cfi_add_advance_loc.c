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
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_5__ {int /*<<< orphan*/ * lab2; int /*<<< orphan*/ * lab1; } ;
struct TYPE_6__ {TYPE_1__ ll; } ;
struct cfi_insn_data {TYPE_2__ u; int /*<<< orphan*/  insn; } ;
struct TYPE_8__ {TYPE_3__* frch_cfi_data; } ;
struct TYPE_7__ {int /*<<< orphan*/ * last_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_CFA_advance_loc ; 
 struct cfi_insn_data* alloc_cfi_insn_data () ; 
 TYPE_4__* frchain_now ; 

void
cfi_add_advance_loc (symbolS *label)
{
  struct cfi_insn_data *insn = alloc_cfi_insn_data ();

  insn->insn = DW_CFA_advance_loc;
  insn->u.ll.lab1 = frchain_now->frch_cfi_data->last_address;
  insn->u.ll.lab2 = label;

  frchain_now->frch_cfi_data->last_address = label;
}