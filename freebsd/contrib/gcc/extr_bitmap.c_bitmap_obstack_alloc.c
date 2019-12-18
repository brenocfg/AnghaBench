#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  obstack; TYPE_2__* heads; } ;
typedef  TYPE_1__ bitmap_obstack ;
typedef  TYPE_2__* bitmap ;
struct TYPE_10__ {scalar_t__ first; } ;

/* Variables and functions */
 TYPE_2__* XOBNEW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ bitmap_default_obstack ; 
 int /*<<< orphan*/  bitmap_head ; 
 int /*<<< orphan*/  bitmap_initialize (TYPE_2__*,TYPE_1__*) ; 

bitmap
bitmap_obstack_alloc (bitmap_obstack *bit_obstack)
{
  bitmap map;

  if (!bit_obstack)
    bit_obstack = &bitmap_default_obstack;
  map = bit_obstack->heads;
  if (map)
    bit_obstack->heads = (void *)map->first;
  else
    map = XOBNEW (&bit_obstack->obstack, bitmap_head);
  bitmap_initialize (map, bit_obstack);

  return map;
}