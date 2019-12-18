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
struct interp {struct interp* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_interps () ; 
 struct interp* interp_list ; 
 int /*<<< orphan*/ * interp_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interpreter_initialized ; 

void
interp_add (struct interp *interp)
{
  if (!interpreter_initialized)
    initialize_interps ();

  gdb_assert (interp_lookup (interp->name) == NULL);

  interp->next = interp_list;
  interp_list = interp;
}