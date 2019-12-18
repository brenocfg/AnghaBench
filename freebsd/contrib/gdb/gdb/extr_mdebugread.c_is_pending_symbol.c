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
struct mdebug_pending {char* s; struct mdebug_pending* next; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fdr; } ;
typedef  int /*<<< orphan*/  FDR ;

/* Variables and functions */
 TYPE_1__* debug_info ; 
 struct mdebug_pending** pending_list ; 

__attribute__((used)) static struct mdebug_pending *
is_pending_symbol (FDR *fh, char *sh)
{
  int f_idx = fh - debug_info->fdr;
  struct mdebug_pending *p;

  /* Linear search is ok, list is typically no more than 10 deep */
  for (p = pending_list[f_idx]; p; p = p->next)
    if (p->s == sh)
      break;
  return p;
}