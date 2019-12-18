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
struct mem_ref {int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
memref_eq (const void *obj1, const void *obj2)
{
  const struct mem_ref *mem1 = obj1;

  return operand_equal_p (mem1->mem, (tree) obj2, 0);
}