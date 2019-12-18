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
 int /*<<< orphan*/  frag_grow (int) ; 
 TYPE_1__* frchain_now ; 
 int /*<<< orphan*/  obstack_blank_fast (int /*<<< orphan*/ *,int) ; 
 char* obstack_next_free (int /*<<< orphan*/ *) ; 

char *
frag_more (int nchars)
{
  register char *retval;

  frag_alloc_check (&frchain_now->frch_obstack);
  frag_grow (nchars);
  retval = obstack_next_free (&frchain_now->frch_obstack);
  obstack_blank_fast (&frchain_now->frch_obstack, nchars);
  return (retval);
}