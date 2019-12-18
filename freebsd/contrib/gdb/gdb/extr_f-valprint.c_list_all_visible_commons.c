#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/  name; int /*<<< orphan*/  owning_function; } ;
typedef  TYPE_1__* SAVED_F77_COMMON_PTR ;

/* Variables and functions */
 TYPE_1__* head_common_list ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
list_all_visible_commons (char *funname)
{
  SAVED_F77_COMMON_PTR tmp;

  tmp = head_common_list;

  printf_filtered ("All COMMON blocks visible at this level:\n\n");

  while (tmp != NULL)
    {
      if (strcmp (tmp->owning_function, funname) == 0)
	printf_filtered ("%s\n", tmp->name);

      tmp = tmp->next;
    }
}