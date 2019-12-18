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
 int /*<<< orphan*/  clean_read_ptr ; 
 int /*<<< orphan*/  repl_write_ptr ; 
 int /*<<< orphan*/  saved_clean_read_ptr ; 
 int /*<<< orphan*/  saved_repl_write_ptr ; 

__attribute__((used)) static void
restore_pointers (void)
{
  clean_read_ptr = saved_clean_read_ptr;
  repl_write_ptr = saved_repl_write_ptr;
}