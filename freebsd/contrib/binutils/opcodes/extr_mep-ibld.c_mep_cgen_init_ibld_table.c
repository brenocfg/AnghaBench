#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  set_vma_operand; int /*<<< orphan*/  get_vma_operand; int /*<<< orphan*/  set_int_operand; int /*<<< orphan*/  get_int_operand; int /*<<< orphan*/  extract_operand; int /*<<< orphan*/  insert_operand; int /*<<< orphan*/ * extract_handlers; int /*<<< orphan*/ * insert_handlers; } ;
typedef  TYPE_1__* CGEN_CPU_DESC ;

/* Variables and functions */
 int /*<<< orphan*/ * mep_cgen_extract_handlers ; 
 int /*<<< orphan*/  mep_cgen_extract_operand ; 
 int /*<<< orphan*/  mep_cgen_get_int_operand ; 
 int /*<<< orphan*/  mep_cgen_get_vma_operand ; 
 int /*<<< orphan*/ * mep_cgen_insert_handlers ; 
 int /*<<< orphan*/  mep_cgen_insert_operand ; 
 int /*<<< orphan*/  mep_cgen_set_int_operand ; 
 int /*<<< orphan*/  mep_cgen_set_vma_operand ; 

void
mep_cgen_init_ibld_table (CGEN_CPU_DESC cd)
{
  cd->insert_handlers = & mep_cgen_insert_handlers[0];
  cd->extract_handlers = & mep_cgen_extract_handlers[0];

  cd->insert_operand = mep_cgen_insert_operand;
  cd->extract_operand = mep_cgen_extract_operand;

  cd->get_int_operand = mep_cgen_get_int_operand;
  cd->set_int_operand = mep_cgen_set_int_operand;
  cd->get_vma_operand = mep_cgen_get_vma_operand;
  cd->set_vma_operand = mep_cgen_set_vma_operand;
}