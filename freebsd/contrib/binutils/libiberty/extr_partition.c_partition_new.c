#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct partition_elem {int dummy; } ;
struct partition_def {int dummy; } ;
typedef  TYPE_2__* partition ;
struct TYPE_5__ {int num_elements; TYPE_1__* elements; } ;
struct TYPE_4__ {int class_element; int class_count; struct TYPE_4__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmalloc (int) ; 

partition
partition_new (int num_elements)
{
  int e;
  
  partition part = (partition) 
    xmalloc (sizeof (struct partition_def) + 
	     (num_elements - 1) * sizeof (struct partition_elem));
  part->num_elements = num_elements;
  for (e = 0; e < num_elements; ++e) 
    {
      part->elements[e].class_element = e;
      part->elements[e].next = &(part->elements[e]);
      part->elements[e].class_count = 1;
    }

  return part;
}