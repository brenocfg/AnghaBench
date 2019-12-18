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
struct work_stuff {int ntypes; int /*<<< orphan*/ ** typevec; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
forget_types (struct work_stuff *work)
{
  int i;

  while (work -> ntypes > 0)
    {
      i = --(work -> ntypes);
      if (work -> typevec[i] != NULL)
	{
	  free (work -> typevec[i]);
	  work -> typevec[i] = NULL;
	}
    }
}