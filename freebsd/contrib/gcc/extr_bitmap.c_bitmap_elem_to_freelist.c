#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* elements; } ;
typedef  TYPE_1__ bitmap_obstack ;
struct TYPE_8__ {struct TYPE_8__* prev; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ bitmap_element ;
typedef  TYPE_3__* bitmap ;
struct TYPE_9__ {TYPE_1__* obstack; } ;

/* Variables and functions */
 TYPE_2__* bitmap_ggc_free ; 

__attribute__((used)) static inline void
bitmap_elem_to_freelist (bitmap head, bitmap_element *elt)
{
  bitmap_obstack *bit_obstack = head->obstack;

  elt->next = NULL;
  if (bit_obstack)
    {
      elt->prev = bit_obstack->elements;
      bit_obstack->elements = elt;
    }
  else
    {
      elt->prev = bitmap_ggc_free;
      bitmap_ggc_free = elt;
    }
}