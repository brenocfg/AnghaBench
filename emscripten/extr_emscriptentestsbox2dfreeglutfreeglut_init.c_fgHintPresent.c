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
typedef  int /*<<< orphan*/  Window ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int /*<<< orphan*/  XA_ATOM ; 
 int fghGetWindowProperty (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned char**) ; 
 scalar_t__** malloc (int) ; 

int fgHintPresent(Window window, Atom property, Atom hint)
{
  Atom ** atoms_ptr;
  int number_of_atoms;
  int supported;
  int i;

  supported = 0;

  atoms_ptr = malloc(sizeof(Atom *));
  number_of_atoms = fghGetWindowProperty(window,
					 property,
					 XA_ATOM,
					 (unsigned char **) atoms_ptr);
  for (i = 0; i < number_of_atoms; i++)
    {
      if ((*atoms_ptr)[i] == hint)
      {
          supported = 1;
          break;
      }
    }

  return supported;
}