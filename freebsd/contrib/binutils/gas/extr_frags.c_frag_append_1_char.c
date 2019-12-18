#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  frch_obstack; } ;

/* Variables and functions */
 int /*<<< orphan*/  frag_alloc_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frag_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_now ; 
 int /*<<< orphan*/  frag_wane (int /*<<< orphan*/ ) ; 
 TYPE_1__* frchain_now ; 
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ *,int) ; 
 int obstack_room (int /*<<< orphan*/ *) ; 

void
frag_append_1_char (int datum)
{
  frag_alloc_check (&frchain_now->frch_obstack);
  if (obstack_room (&frchain_now->frch_obstack) <= 1)
    {
      frag_wane (frag_now);
      frag_new (0);
    }
  obstack_1grow (&frchain_now->frch_obstack, datum);
}