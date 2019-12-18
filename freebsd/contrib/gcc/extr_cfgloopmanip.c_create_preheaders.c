#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct loops {unsigned int num; int /*<<< orphan*/  state; int /*<<< orphan*/ * parray; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOOPS_HAVE_PREHEADERS ; 
 int /*<<< orphan*/  create_preheader (int /*<<< orphan*/ ,int) ; 

void
create_preheaders (struct loops *loops, int flags)
{
  unsigned i;
  for (i = 1; i < loops->num; i++)
    create_preheader (loops->parray[i], flags);
  loops->state |= LOOPS_HAVE_PREHEADERS;
}