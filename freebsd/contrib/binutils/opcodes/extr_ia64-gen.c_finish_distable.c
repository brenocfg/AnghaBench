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
struct disent {int ournum; int nextcnt; struct disent* next_ent; } ;

/* Variables and functions */
 struct disent* disinsntable ; 

__attribute__((used)) static void
finish_distable ()
{
  struct disent *ent = disinsntable;
  struct disent *prev = ent;

  ent->ournum = 32768;
  while ((ent = ent->next_ent) != NULL)
    {
      ent->ournum = prev->ournum + prev->nextcnt + 1;
      prev = ent;
    }
}