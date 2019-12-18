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
struct work_stuff {int /*<<< orphan*/ * ktypevec; int /*<<< orphan*/ * btypevec; } ;

/* Variables and functions */
 int /*<<< orphan*/  forget_B_and_K_types (struct work_stuff*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void
squangle_mop_up (struct work_stuff *work)
{
  /* clean up the B and K type mangling types. */
  forget_B_and_K_types (work);
  if (work -> btypevec != NULL)
    {
      free ((char *) work -> btypevec);
    }
  if (work -> ktypevec != NULL)
    {
      free ((char *) work -> ktypevec);
    }
}