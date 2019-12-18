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
struct diff_block {struct diff_block* next; } ;
struct diff3_block {struct diff3_block* next; } ;
typedef  scalar_t__ lin ;

/* Variables and functions */
 scalar_t__ D_HIGHLINE (struct diff_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ D_LOWLINE (struct diff_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC ; 
 int /*<<< orphan*/  fatal (char*) ; 
 struct diff3_block* using_to_diff3_block (struct diff_block**,struct diff_block**,int,int,struct diff3_block const*) ; 

__attribute__((used)) static struct diff3_block *
make_3way_diff (struct diff_block *thread0, struct diff_block *thread1)
{
  /* Work on the two diffs passed to it as threads.  Thread number 0
     is diff02, thread number 1 is diff12.  USING is the base of the
     list of blocks to be used to construct each block of the three
     way diff; if no blocks from a particular thread are to be used,
     that element of USING is 0.  LAST_USING contains the last
     elements on each of the using lists.

     HIGH_WATER_MARK is the highest line number in the common file
     described in any of the diffs in either of the USING lists.
     HIGH_WATER_THREAD names the thread.  Similarly BASE_WATER_MARK
     and BASE_WATER_THREAD describe the lowest line number in the
     common file described in any of the diffs in either of the USING
     lists.  HIGH_WATER_DIFF is the diff from which the
     HIGH_WATER_MARK was taken.

     HIGH_WATER_DIFF should always be equal to
     LAST_USING[HIGH_WATER_THREAD].  OTHER_DIFF is the next diff to
     check for higher water, and should always be equal to
     CURRENT[HIGH_WATER_THREAD ^ 1].  OTHER_THREAD is the thread in
     which the OTHER_DIFF is, and hence should always be equal to
     HIGH_WATER_THREAD ^ 1.

     LAST_DIFF is the last diff block produced by this routine, for
     line correspondence purposes between that diff and the one
     currently being worked on.  It is ZERO_DIFF before any blocks
     have been created.  */

  struct diff_block *using[2];
  struct diff_block *last_using[2];
  struct diff_block *current[2];

  lin high_water_mark;

  int high_water_thread;
  int base_water_thread;
  int other_thread;

  struct diff_block *high_water_diff;
  struct diff_block *other_diff;

  struct diff3_block *result;
  struct diff3_block *tmpblock;
  struct diff3_block **result_end;

  struct diff3_block const *last_diff3;

  static struct diff3_block const zero_diff3;

  /* Initialization */
  result = 0;
  result_end = &result;
  current[0] = thread0; current[1] = thread1;
  last_diff3 = &zero_diff3;

  /* Sniff up the threads until we reach the end */

  while (current[0] || current[1])
    {
      using[0] = using[1] = last_using[0] = last_using[1] = 0;

      /* Setup low and high water threads, diffs, and marks.  */
      if (!current[0])
	base_water_thread = 1;
      else if (!current[1])
	base_water_thread = 0;
      else
	base_water_thread =
	  (D_LOWLINE (current[0], FC) > D_LOWLINE (current[1], FC));

      high_water_thread = base_water_thread;

      high_water_diff = current[high_water_thread];

      high_water_mark = D_HIGHLINE (high_water_diff, FC);

      /* Make the diff you just got info from into the using class */
      using[high_water_thread]
	= last_using[high_water_thread]
	= high_water_diff;
      current[high_water_thread] = high_water_diff->next;
      last_using[high_water_thread]->next = 0;

      /* And mark the other diff */
      other_thread = high_water_thread ^ 0x1;
      other_diff = current[other_thread];

      /* Shuffle up the ladder, checking the other diff to see if it
	 needs to be incorporated.  */
      while (other_diff
	     && D_LOWLINE (other_diff, FC) <= high_water_mark + 1)
	{

	  /* Incorporate this diff into the using list.  Note that
	     this doesn't take it off the current list */
	  if (using[other_thread])
	    last_using[other_thread]->next = other_diff;
	  else
	    using[other_thread] = other_diff;
	  last_using[other_thread] = other_diff;

	  /* Take it off the current list.  Note that this following
	     code assumes that other_diff enters it equal to
	     current[high_water_thread ^ 0x1] */
	  current[other_thread] = current[other_thread]->next;
	  other_diff->next = 0;

	  /* Set the high_water stuff
	     If this comparison is equal, then this is the last pass
	     through this loop; since diff blocks within a given
	     thread cannot overlap, the high_water_mark will be
	     *below* the range_start of either of the next diffs.  */

	  if (high_water_mark < D_HIGHLINE (other_diff, FC))
	    {
	      high_water_thread ^= 1;
	      high_water_diff = other_diff;
	      high_water_mark = D_HIGHLINE (other_diff, FC);
	    }

	  /* Set the other diff */
	  other_thread = high_water_thread ^ 0x1;
	  other_diff = current[other_thread];
	}

      /* The using lists contain a list of all of the blocks to be
	 included in this diff3_block.  Create it.  */

      tmpblock = using_to_diff3_block (using, last_using,
				       base_water_thread, high_water_thread,
				       last_diff3);

      if (!tmpblock)
	fatal ("internal error: screwup in format of diff blocks");

      /* Put it on the list.  */
      *result_end = tmpblock;
      result_end = &tmpblock->next;

      /* Set up corresponding lines correctly.  */
      last_diff3 = tmpblock;
    }
  return result;
}