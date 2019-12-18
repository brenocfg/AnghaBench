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
struct target_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  auto_solib_add ; 
 int /*<<< orphan*/  coff_solib_add (char*,int /*<<< orphan*/ ,struct target_ops*,int /*<<< orphan*/ ) ; 

void
coff_solib_create_inferior_hook (void)
{
  coff_solib_add ((char *) 0, 0, (struct target_ops *) 0, auto_solib_add);
}