#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ known; } ;
struct TYPE_4__ {scalar_t__ debug_dv; } ;

/* Variables and functions */
 int NELEMS (TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* gr_values ; 
 TYPE_1__ md ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
clear_register_values ()
{
  int i;
  if (md.debug_dv)
    fprintf (stderr, "  Clearing register values\n");
  for (i = 1; i < NELEMS (gr_values); i++)
    gr_values[i].known = 0;
}