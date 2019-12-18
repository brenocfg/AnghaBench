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
 long FB_LABEL_SPECIAL ; 
 int fb_label_count ; 
 long* fb_label_instances ; 
 long* fb_labels ; 
 long* fb_low_counter ; 

__attribute__((used)) static long
fb_label_instance (long label)
{
  long *i;

  if (label < FB_LABEL_SPECIAL)
    {
      return (fb_low_counter[label]);
    }

  if (fb_labels != NULL)
    {
      for (i = fb_labels + FB_LABEL_SPECIAL;
	   i < fb_labels + fb_label_count; ++i)
	{
	  if (*i == label)
	    {
	      return (fb_label_instances[i - fb_labels]);
	    }			/* if we find it  */
	}			/* for each existing label  */
    }

  /* We didn't find the label, so this must be a reference to the
     first instance.  */
  return 0;
}