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
 long* dollar_label_instances ; 
 long* dollar_labels ; 
 int /*<<< orphan*/  know (int) ; 

__attribute__((used)) static long
dollar_label_instance (long label)
{
  long *i;

  know ((dollar_labels != NULL) || (dollar_label_count == 0));

  for (i = dollar_labels; i < dollar_labels + dollar_label_count; ++i)
    if (*i == label)
      return (dollar_label_instances[i - dollar_labels]);

  /* If we get here, we haven't seen the label before.
     Therefore its instance count is zero.  */
  return 0;
}