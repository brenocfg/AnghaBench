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
 int /*<<< orphan*/  print_objfile_statistics () ; 
 int /*<<< orphan*/  print_symbol_bcache_statistics () ; 

void
maintenance_print_statistics (char *args, int from_tty)
{
  print_objfile_statistics ();
  print_symbol_bcache_statistics ();
}