#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct type {int dummy; } ;
struct mdebug_pending {char* s; struct mdebug_pending* next; struct type* t; } ;
struct TYPE_4__ {int /*<<< orphan*/  objfile_obstack; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fdr; } ;
typedef  int /*<<< orphan*/  FDR ;

/* Variables and functions */
 TYPE_2__* current_objfile ; 
 TYPE_1__* debug_info ; 
 struct mdebug_pending* is_pending_symbol (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 struct mdebug_pending** pending_list ; 

__attribute__((used)) static void
add_pending (FDR *fh, char *sh, struct type *t)
{
  int f_idx = fh - debug_info->fdr;
  struct mdebug_pending *p = is_pending_symbol (fh, sh);

  /* Make sure we do not make duplicates */
  if (!p)
    {
      p = ((struct mdebug_pending *)
	   obstack_alloc (&current_objfile->objfile_obstack,
			  sizeof (struct mdebug_pending)));
      p->s = sh;
      p->t = t;
      p->next = pending_list[f_idx];
      pending_list[f_idx] = p;
    }
}