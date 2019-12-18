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
struct ls_expr {int /*<<< orphan*/  index; struct ls_expr* next; } ;

/* Variables and functions */
 struct ls_expr* pre_ldst_mems ; 

__attribute__((used)) static int
enumerate_ldsts (void)
{
  struct ls_expr * ptr;
  int n = 0;

  for (ptr = pre_ldst_mems; ptr != NULL; ptr = ptr->next)
    ptr->index = n++;

  return n;
}