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
 int DOLLAR_LABEL_BUMP_BY ; 
 int dollar_label_count ; 
 char* dollar_label_defines ; 
 int* dollar_label_instances ; 
 int dollar_label_max ; 
 long* dollar_labels ; 
 char* xmalloc (int) ; 
 char* xrealloc (char*,int) ; 

void
define_dollar_label (long label)
{
  long *i;

  for (i = dollar_labels; i < dollar_labels + dollar_label_count; ++i)
    if (*i == label)
      {
	++dollar_label_instances[i - dollar_labels];
	dollar_label_defines[i - dollar_labels] = 1;
	return;
      }

  /* If we get to here, we don't have label listed yet.  */

  if (dollar_labels == NULL)
    {
      dollar_labels = (long *) xmalloc (DOLLAR_LABEL_BUMP_BY * sizeof (long));
      dollar_label_instances = (long *) xmalloc (DOLLAR_LABEL_BUMP_BY * sizeof (long));
      dollar_label_defines = xmalloc (DOLLAR_LABEL_BUMP_BY);
      dollar_label_max = DOLLAR_LABEL_BUMP_BY;
      dollar_label_count = 0;
    }
  else if (dollar_label_count == dollar_label_max)
    {
      dollar_label_max += DOLLAR_LABEL_BUMP_BY;
      dollar_labels = (long *) xrealloc ((char *) dollar_labels,
					 dollar_label_max * sizeof (long));
      dollar_label_instances = (long *) xrealloc ((char *) dollar_label_instances,
					  dollar_label_max * sizeof (long));
      dollar_label_defines = xrealloc (dollar_label_defines, dollar_label_max);
    }				/* if we needed to grow  */

  dollar_labels[dollar_label_count] = label;
  dollar_label_instances[dollar_label_count] = 1;
  dollar_label_defines[dollar_label_count] = 1;
  ++dollar_label_count;
}