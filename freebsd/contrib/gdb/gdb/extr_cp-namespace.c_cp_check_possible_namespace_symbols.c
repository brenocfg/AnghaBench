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
struct objfile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_possible_namespace_symbols_loop (char const*,int /*<<< orphan*/ ,struct objfile*) ; 
 int /*<<< orphan*/  cp_find_first_component (char const*) ; 

void
cp_check_possible_namespace_symbols (const char *name, struct objfile *objfile)
{
  check_possible_namespace_symbols_loop (name,
					 cp_find_first_component (name),
					 objfile);
}