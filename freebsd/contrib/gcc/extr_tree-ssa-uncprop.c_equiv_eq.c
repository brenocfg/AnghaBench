#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct equiv_hash_elt {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
equiv_eq (const void *p1, const void *p2)
{
  tree value1 = ((struct equiv_hash_elt *)p1)->value;
  tree value2 = ((struct equiv_hash_elt *)p2)->value;

  return operand_equal_p (value1, value2, 0);
}