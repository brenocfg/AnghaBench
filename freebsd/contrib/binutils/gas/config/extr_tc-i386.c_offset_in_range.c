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
typedef  int offsetT ;
typedef  int addressT ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sprint_value (char*,int) ; 
 int /*<<< orphan*/  use_rela_relocations ; 

__attribute__((used)) static offsetT
offset_in_range (offsetT val, int size)
{
  addressT mask;

  switch (size)
    {
    case 1: mask = ((addressT) 1 <<  8) - 1; break;
    case 2: mask = ((addressT) 1 << 16) - 1; break;
    case 4: mask = ((addressT) 2 << 31) - 1; break;
#ifdef BFD64
    case 8: mask = ((addressT) 2 << 63) - 1; break;
#endif
    default: abort ();
    }

  /* If BFD64, sign extend val.  */
  if (!use_rela_relocations)
    if ((val & ~(((addressT) 2 << 31) - 1)) == 0)
      val = (val ^ ((addressT) 1 << 31)) - ((addressT) 1 << 31);

  if ((val & ~mask) != 0 && (val & ~mask) != ~mask)
    {
      char buf1[40], buf2[40];

      sprint_value (buf1, val);
      sprint_value (buf2, val & mask);
      as_warn (_("%s shortened to %s"), buf1, buf2);
    }
  return val & mask;
}