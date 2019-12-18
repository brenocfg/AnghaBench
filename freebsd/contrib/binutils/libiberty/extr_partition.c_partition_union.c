#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct partition_elem {int class_element; scalar_t__ class_count; struct partition_elem* next; } ;
typedef  TYPE_1__* partition ;
struct TYPE_3__ {struct partition_elem* elements; } ;

/* Variables and functions */

int
partition_union (partition part, int elem1, int elem2)
{
  struct partition_elem *elements = part->elements;
  struct partition_elem *e1;
  struct partition_elem *e2;
  struct partition_elem *p;
  struct partition_elem *old_next;
  /* The canonical element of the resulting union class.  */
  int class_element = elements[elem1].class_element;

  /* If they're already in the same class, do nothing.  */
  if (class_element == elements[elem2].class_element)
    return class_element;

  /* Make sure ELEM1 is in the larger class of the two.  If not, swap
     them.  This way we always scan the shorter list.  */
  if (elements[elem1].class_count < elements[elem2].class_count) 
    {
      int temp = elem1;
      elem1 = elem2;
      elem2 = temp;
      class_element = elements[elem1].class_element;
    }

  e1 = &(elements[elem1]);
  e2 = &(elements[elem2]);

  /* Keep a count of the number of elements in the list.  */
  elements[class_element].class_count 
    += elements[e2->class_element].class_count;

  /* Update the class fields in elem2's class list.  */
  e2->class_element = class_element;
  for (p = e2->next; p != e2; p = p->next)
    p->class_element = class_element;
  
  /* Splice ELEM2's class list into ELEM1's.  These are circular
     lists.  */
  old_next = e1->next;
  e1->next = e2->next;
  e2->next = old_next;

  return class_element;
}