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

/* Variables and functions */

__attribute__((used)) static unsigned int
atof_vax_sizeof (int letter)
{
  int return_value;

  /* Permitting uppercase letters is probably a bad idea.
     Please use only lower-cased letters in case the upper-cased
     ones become unsupported!  */
  switch (letter)
    {
    case 'f':
    case 'F':
      return_value = 4;
      break;

    case 'd':
    case 'D':
    case 'g':
    case 'G':
      return_value = 8;
      break;

    case 'h':
    case 'H':
      return_value = 16;
      break;

    default:
      return_value = 0;
      break;
    }

  return return_value;
}