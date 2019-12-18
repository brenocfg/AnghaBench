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
struct builtin_description {int code; int /*<<< orphan*/  mask; } ;
typedef  enum rs6000_builtins { ____Placeholder_rs6000_builtins } rs6000_builtins ;

/* Variables and functions */
 int /*<<< orphan*/  target_flags ; 

__attribute__((used)) static void
enable_mask_for_builtins (struct builtin_description *desc, int size,
			  enum rs6000_builtins start,
			  enum rs6000_builtins end)
{
  int i;

  for (i = 0; i < size; ++i)
    if (desc[i].code == start)
      break;

  if (i == size)
    return;

  for (; i < size; ++i)
    {
      /* Flip all the bits on.  */
      desc[i].mask = target_flags;
      if (desc[i].code == end)
	break;
    }
}