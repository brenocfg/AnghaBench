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
typedef  int /*<<< orphan*/  offsetT ;
struct TYPE_4__ {TYPE_1__* frch_cfi_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  cur_cfa_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_CFA_def_cfa_offset ; 
 int /*<<< orphan*/  cfi_add_CFA_insn_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* frchain_now ; 

void
cfi_add_CFA_def_cfa_offset (offsetT offset)
{
  cfi_add_CFA_insn_offset (DW_CFA_def_cfa_offset, offset);
  frchain_now->frch_cfi_data->cur_cfa_offset = offset;
}