#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  obstack; int /*<<< orphan*/ * heads; int /*<<< orphan*/ * elements; } ;
typedef  TYPE_1__ bitmap_obstack ;

/* Variables and functions */
 TYPE_1__ bitmap_default_obstack ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bitmap_obstack_release (bitmap_obstack *bit_obstack)
{
  if (!bit_obstack)
    bit_obstack = &bitmap_default_obstack;

  bit_obstack->elements = NULL;
  bit_obstack->heads = NULL;
  obstack_free (&bit_obstack->obstack, NULL);
}