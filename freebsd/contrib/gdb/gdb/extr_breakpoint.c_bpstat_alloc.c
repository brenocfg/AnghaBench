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
struct breakpoint {int dummy; } ;
typedef  TYPE_1__* bpstat ;
struct TYPE_4__ {int /*<<< orphan*/  print_it; int /*<<< orphan*/ * old_val; int /*<<< orphan*/ * commands; struct breakpoint* breakpoint_at; struct TYPE_4__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_it_normal ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static bpstat
bpstat_alloc (struct breakpoint *b, bpstat cbs /* Current "bs" value */ )
{
  bpstat bs;

  bs = (bpstat) xmalloc (sizeof (*bs));
  cbs->next = bs;
  bs->breakpoint_at = b;
  /* If the condition is false, etc., don't do the commands.  */
  bs->commands = NULL;
  bs->old_val = NULL;
  bs->print_it = print_it_normal;
  return bs;
}