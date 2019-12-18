#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sub; int /*<<< orphan*/  formal_hash; TYPE_2__* formals; } ;
typedef  TYPE_1__ macro_entry ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ formal_entry ;

/* Variables and functions */
 int /*<<< orphan*/  del_formal (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hash_die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_macro(macro_entry *macro)
{
  formal_entry *formal;

  for (formal = macro->formals; formal; )
    {
      formal_entry *f;

      f = formal;
      formal = formal->next;
      del_formal (f);
    }
  hash_die (macro->formal_hash);
  sb_kill (&macro->sub);
  free (macro);
}