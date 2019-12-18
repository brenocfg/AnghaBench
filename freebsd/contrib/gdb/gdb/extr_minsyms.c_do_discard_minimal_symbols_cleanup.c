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
struct msym_bunch {struct msym_bunch* next; } ;

/* Variables and functions */
 struct msym_bunch* msym_bunch ; 
 int /*<<< orphan*/  xfree (struct msym_bunch*) ; 

__attribute__((used)) static void
do_discard_minimal_symbols_cleanup (void *arg)
{
  struct msym_bunch *next;

  while (msym_bunch != NULL)
    {
      next = msym_bunch->next;
      xfree (msym_bunch);
      msym_bunch = next;
    }
}