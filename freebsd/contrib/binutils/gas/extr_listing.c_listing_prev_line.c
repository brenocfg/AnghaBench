#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  frag; struct TYPE_6__* next; } ;
typedef  TYPE_1__ list_info_type ;
struct TYPE_7__ {TYPE_1__* line; struct TYPE_7__* fr_next; } ;
typedef  TYPE_2__ fragS ;
struct TYPE_8__ {TYPE_2__* frch_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  frag_now ; 
 TYPE_5__* frchain_now ; 
 TYPE_1__* head ; 
 TYPE_1__* listing_tail ; 
 int /*<<< orphan*/  new_frag () ; 

void
listing_prev_line (void)
{
  list_info_type *l;
  fragS *f;

  if (head == (list_info_type *) NULL
      || head == listing_tail)
    return;

  new_frag ();

  for (l = head; l->next != listing_tail; l = l->next)
    ;

  for (f = frchain_now->frch_root; f != (fragS *) NULL; f = f->fr_next)
    if (f->line == listing_tail)
      f->line = l;

  listing_tail->frag = frag_now;
  new_frag ();
}