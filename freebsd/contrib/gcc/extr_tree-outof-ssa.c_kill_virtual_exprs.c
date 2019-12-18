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
typedef  int /*<<< orphan*/  temp_expr_table_p ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTUAL_PARTITION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
kill_virtual_exprs (temp_expr_table_p tab, bool clear_bit)
{
  kill_expr (tab, VIRTUAL_PARTITION (tab), clear_bit);
}