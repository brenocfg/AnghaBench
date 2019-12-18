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
 int /*<<< orphan*/  regcache_dump_cooked ; 
 int /*<<< orphan*/  regcache_print (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
maintenance_print_cooked_registers (char *args, int from_tty)
{
  regcache_print (args, regcache_dump_cooked);
}