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
 scalar_t__ canon_modify_mem_list ; 
 int /*<<< orphan*/  clear_modify_mem_tables () ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ modify_mem_list ; 

__attribute__((used)) static void
free_modify_mem_tables (void)
{
  clear_modify_mem_tables ();
  free (modify_mem_list);
  free (canon_modify_mem_list);
  modify_mem_list = 0;
  canon_modify_mem_list = 0;
}