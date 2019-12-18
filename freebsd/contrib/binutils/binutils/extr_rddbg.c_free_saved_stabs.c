#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * string; } ;

/* Variables and functions */
 int SAVE_STABS_COUNT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__* saved_stabs ; 
 scalar_t__ saved_stabs_index ; 

__attribute__((used)) static void
free_saved_stabs (void)
{
  int i;

  for (i = 0; i < SAVE_STABS_COUNT; i++)
    {
      if (saved_stabs[i].string != NULL)
	{
	  free (saved_stabs[i].string);
	  saved_stabs[i].string = NULL;
	}
    }

  saved_stabs_index = 0;
}