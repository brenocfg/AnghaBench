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
struct file_data {char* changed; size_t* equivs; size_t buffered_lines; } ;
typedef  size_t lin ;

/* Variables and functions */

__attribute__((used)) static void
shift_boundaries (struct file_data filevec[])
{
  int f;

  for (f = 0; f < 2; f++)
    {
      char *changed = filevec[f].changed;
      char *other_changed = filevec[1 - f].changed;
      lin const *equivs = filevec[f].equivs;
      lin i = 0;
      lin j = 0;
      lin i_end = filevec[f].buffered_lines;

      while (1)
	{
	  lin runlength, start, corresponding;

	  /* Scan forwards to find beginning of another run of changes.
	     Also keep track of the corresponding point in the other file.  */

	  while (i < i_end && !changed[i])
	    {
	      while (other_changed[j++])
		continue;
	      i++;
	    }

	  if (i == i_end)
	    break;

	  start = i;

	  /* Find the end of this run of changes.  */

	  while (changed[++i])
	    continue;
	  while (other_changed[j])
	    j++;

	  do
	    {
	      /* Record the length of this run of changes, so that
		 we can later determine whether the run has grown.  */
	      runlength = i - start;

	      /* Move the changed region back, so long as the
		 previous unchanged line matches the last changed one.
		 This merges with previous changed regions.  */

	      while (start && equivs[start - 1] == equivs[i - 1])
		{
		  changed[--start] = 1;
		  changed[--i] = 0;
		  while (changed[start - 1])
		    start--;
		  while (other_changed[--j])
		    continue;
		}

	      /* Set CORRESPONDING to the end of the changed run, at the last
		 point where it corresponds to a changed run in the other file.
		 CORRESPONDING == I_END means no such point has been found.  */
	      corresponding = other_changed[j - 1] ? i : i_end;

	      /* Move the changed region forward, so long as the
		 first changed line matches the following unchanged one.
		 This merges with following changed regions.
		 Do this second, so that if there are no merges,
		 the changed region is moved forward as far as possible.  */

	      while (i != i_end && equivs[start] == equivs[i])
		{
		  changed[start++] = 0;
		  changed[i++] = 1;
		  while (changed[i])
		    i++;
		  while (other_changed[++j])
		    corresponding = i;
		}
	    }
	  while (runlength != i - start);

	  /* If possible, move the fully-merged run of changes
	     back to a corresponding run in the other file.  */

	  while (corresponding < i)
	    {
	      changed[--start] = 1;
	      changed[--i] = 0;
	      while (other_changed[--j])
		continue;
	    }
	}
    }
}