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
typedef  scalar_t__ tre_tag_direction_t ;

/* Variables and functions */
 scalar_t__ TRE_TAG_MINIMIZE ; 

__attribute__((used)) static int
tre_tag_order(int num_tags, tre_tag_direction_t *tag_directions,
	      int *t1, int *t2)
{
  int i;
  for (i = 0; i < num_tags; i++)
    {
      if (tag_directions[i] == TRE_TAG_MINIMIZE)
	{
	  if (t1[i] < t2[i])
	    return 1;
	  if (t1[i] > t2[i])
	    return 0;
	}
      else
	{
	  if (t1[i] > t2[i])
	    return 1;
	  if (t1[i] < t2[i])
	    return 0;
	}
    }
  /*  assert(0);*/
  return 0;
}