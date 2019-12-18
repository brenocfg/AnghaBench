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
 scalar_t__ dollar_label_count ; 
 int* dollar_label_defines ; 
 long* dollar_labels ; 
 int /*<<< orphan*/  know (int) ; 

int
dollar_label_defined (long label)
{
  long *i;

  know ((dollar_labels != NULL) || (dollar_label_count == 0));

  for (i = dollar_labels; i < dollar_labels + dollar_label_count; ++i)
    if (*i == label)
      return dollar_label_defines[i - dollar_labels];

  /* If we get here, label isn't defined.  */
  return 0;
}