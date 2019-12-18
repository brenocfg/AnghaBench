#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* operand_entry_t ;
typedef  int /*<<< orphan*/  hashval_t ;
struct TYPE_2__ {int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int /*<<< orphan*/  iterative_hash_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
operand_entry_hash (const void *p)
{
  const operand_entry_t vr = (operand_entry_t) p;
  return iterative_hash_expr (vr->op, 0);
}