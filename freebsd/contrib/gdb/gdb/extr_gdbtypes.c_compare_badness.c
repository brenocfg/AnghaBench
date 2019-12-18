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
struct badness_vector {int length; int* rank; } ;

/* Variables and functions */

int
compare_badness (struct badness_vector *a, struct badness_vector *b)
{
  int i;
  int tmp;
  short found_pos = 0;		/* any positives in c? */
  short found_neg = 0;		/* any negatives in c? */

  /* differing lengths => incomparable */
  if (a->length != b->length)
    return 1;

  /* Subtract b from a */
  for (i = 0; i < a->length; i++)
    {
      tmp = a->rank[i] - b->rank[i];
      if (tmp > 0)
	found_pos = 1;
      else if (tmp < 0)
	found_neg = 1;
    }

  if (found_pos)
    {
      if (found_neg)
	return 1;		/* incomparable */
      else
	return 3;		/* A > B */
    }
  else
    /* no positives */
    {
      if (found_neg)
	return 2;		/* A < B */
      else
	return 0;		/* A == B */
    }
}