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
 int /*<<< orphan*/  c_register_pragma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_register_pragma_with_expansion (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solaris_pragma_align ; 
 int /*<<< orphan*/  solaris_pragma_fini ; 
 int /*<<< orphan*/  solaris_pragma_init ; 

void
solaris_register_pragmas (void)
{
  c_register_pragma_with_expansion (0, "align", solaris_pragma_align);
  c_register_pragma (0, "init", solaris_pragma_init);
  c_register_pragma (0, "fini", solaris_pragma_fini);
}