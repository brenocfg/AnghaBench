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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  finish_mangling (int) ; 
 int /*<<< orphan*/  get_identifier_nocopy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_mangling (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  write_name (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_string (char*) ; 

tree
mangle_ref_init_variable (const tree variable)
{
  start_mangling (variable, /*ident_p=*/true);
  write_string ("_ZGR");
  write_name (variable, /*ignore_local_scope=*/0);
  return get_identifier_nocopy (finish_mangling (/*warn=*/false));
}