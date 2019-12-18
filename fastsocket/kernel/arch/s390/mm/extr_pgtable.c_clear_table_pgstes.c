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

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  _PAGE_TYPE_EMPTY ; 
 int /*<<< orphan*/  clear_table (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int) ; 

void clear_table_pgstes(unsigned long *table)
{
	clear_table(table, _PAGE_TYPE_EMPTY, PAGE_SIZE/4);
	memset(table + 256, 0, PAGE_SIZE/4);
	clear_table(table + 512, _PAGE_TYPE_EMPTY, PAGE_SIZE/4);
	memset(table + 768, 0, PAGE_SIZE/4);
}