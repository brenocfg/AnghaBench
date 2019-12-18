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
struct ls_expr {struct ls_expr* next; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ls_expr *
next_ls_expr (struct ls_expr * ptr)
{
  return ptr->next;
}