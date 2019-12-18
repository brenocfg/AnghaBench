#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* use_operand_p ;
struct TYPE_6__ {TYPE_1__* imm_use; int /*<<< orphan*/  next_imm_name; } ;
typedef  TYPE_2__ imm_use_iterator ;
struct TYPE_5__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */

__attribute__((used)) static inline use_operand_p
first_imm_use_on_stmt (imm_use_iterator *imm)
{
  imm->next_imm_name = imm->imm_use->next;
  return imm->imm_use;
}