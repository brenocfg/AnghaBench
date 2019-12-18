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
struct target_ops {struct target_ops* to_sections; int /*<<< orphan*/  to_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct target_ops*) ; 

void
target_bfd_xclose (struct target_ops *t, int quitting)
{
  bfd_close (t->to_data);
  xfree (t->to_sections);
  xfree (t);
}