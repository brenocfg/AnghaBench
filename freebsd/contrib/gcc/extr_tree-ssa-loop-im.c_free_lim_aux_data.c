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
struct lim_aux_data {struct lim_aux_data* next; struct lim_aux_data* depends; } ;
struct depend {struct depend* next; struct depend* depends; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct lim_aux_data*) ; 

__attribute__((used)) static void
free_lim_aux_data (struct lim_aux_data *data)
{
  struct depend *dep, *next;

  for (dep = data->depends; dep; dep = next)
    {
      next = dep->next;
      free (dep);
    }
  free (data);
}