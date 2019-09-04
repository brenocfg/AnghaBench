#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ position; int assertions; int* tags; int /*<<< orphan*/  backref; int /*<<< orphan*/  neg_classes; int /*<<< orphan*/  class; int /*<<< orphan*/  code_max; int /*<<< orphan*/  code_min; } ;
typedef  TYPE_1__ tre_pos_and_tags_t ;
typedef  int /*<<< orphan*/  tre_mem_t ;

/* Variables and functions */
 int* tre_mem_alloc (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* tre_mem_calloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tre_pos_and_tags_t *
tre_set_union(tre_mem_t mem, tre_pos_and_tags_t *set1, tre_pos_and_tags_t *set2,
	      int *tags, int assertions)
{
  int s1, s2, i, j;
  tre_pos_and_tags_t *new_set;
  int *new_tags;
  int num_tags;

  for (num_tags = 0; tags != NULL && tags[num_tags] >= 0; num_tags++);
  for (s1 = 0; set1[s1].position >= 0; s1++);
  for (s2 = 0; set2[s2].position >= 0; s2++);
  new_set = tre_mem_calloc(mem, sizeof(*new_set) * (s1 + s2 + 1));
  if (!new_set )
    return NULL;

  for (s1 = 0; set1[s1].position >= 0; s1++)
    {
      new_set[s1].position = set1[s1].position;
      new_set[s1].code_min = set1[s1].code_min;
      new_set[s1].code_max = set1[s1].code_max;
      new_set[s1].assertions = set1[s1].assertions | assertions;
      new_set[s1].class = set1[s1].class;
      new_set[s1].neg_classes = set1[s1].neg_classes;
      new_set[s1].backref = set1[s1].backref;
      if (set1[s1].tags == NULL && tags == NULL)
	new_set[s1].tags = NULL;
      else
	{
	  for (i = 0; set1[s1].tags != NULL && set1[s1].tags[i] >= 0; i++);
	  new_tags = tre_mem_alloc(mem, (sizeof(*new_tags)
					 * (i + num_tags + 1)));
	  if (new_tags == NULL)
	    return NULL;
	  for (j = 0; j < i; j++)
	    new_tags[j] = set1[s1].tags[j];
	  for (i = 0; i < num_tags; i++)
	    new_tags[j + i] = tags[i];
	  new_tags[j + i] = -1;
	  new_set[s1].tags = new_tags;
	}
    }

  for (s2 = 0; set2[s2].position >= 0; s2++)
    {
      new_set[s1 + s2].position = set2[s2].position;
      new_set[s1 + s2].code_min = set2[s2].code_min;
      new_set[s1 + s2].code_max = set2[s2].code_max;
      /* XXX - why not | assertions here as well? */
      new_set[s1 + s2].assertions = set2[s2].assertions;
      new_set[s1 + s2].class = set2[s2].class;
      new_set[s1 + s2].neg_classes = set2[s2].neg_classes;
      new_set[s1 + s2].backref = set2[s2].backref;
      if (set2[s2].tags == NULL)
	new_set[s1 + s2].tags = NULL;
      else
	{
	  for (i = 0; set2[s2].tags[i] >= 0; i++);
	  new_tags = tre_mem_alloc(mem, sizeof(*new_tags) * (i + 1));
	  if (new_tags == NULL)
	    return NULL;
	  for (j = 0; j < i; j++)
	    new_tags[j] = set2[s2].tags[j];
	  new_tags[j] = -1;
	  new_set[s1 + s2].tags = new_tags;
	}
    }
  new_set[s1 + s2].position = -1;
  return new_set;
}