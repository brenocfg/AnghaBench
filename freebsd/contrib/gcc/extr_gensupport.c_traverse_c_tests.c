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
typedef  int /*<<< orphan*/  htab_trav ;

/* Variables and functions */
 scalar_t__ condition_table ; 
 int /*<<< orphan*/  htab_traverse (scalar_t__,int /*<<< orphan*/ ,void*) ; 

void
traverse_c_tests (htab_trav callback, void *info)
{
  if (condition_table)
    htab_traverse (condition_table, callback, info);
}