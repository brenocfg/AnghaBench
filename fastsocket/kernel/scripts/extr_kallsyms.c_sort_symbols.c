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
struct sym_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  compare_symbols ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table ; 
 int /*<<< orphan*/  table_cnt ; 

__attribute__((used)) static void sort_symbols(void)
{
	qsort(table, table_cnt, sizeof(struct sym_entry), compare_symbols);
}