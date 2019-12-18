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
struct work_stuff {int numk; int numb; int /*<<< orphan*/ ** btypevec; int /*<<< orphan*/ ** ktypevec; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
forget_B_and_K_types (struct work_stuff *work)
{
  int i;

  while (work -> numk > 0)
    {
      i = --(work -> numk);
      if (work -> ktypevec[i] != NULL)
	{
	  free (work -> ktypevec[i]);
	  work -> ktypevec[i] = NULL;
	}
    }

  while (work -> numb > 0)
    {
      i = --(work -> numb);
      if (work -> btypevec[i] != NULL)
	{
	  free (work -> btypevec[i]);
	  work -> btypevec[i] = NULL;
	}
    }
}