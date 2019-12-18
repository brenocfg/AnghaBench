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
struct TYPE_2__ {int ordering; } ;

/* Variables and functions */
 int /*<<< orphan*/  give_switch (int,int /*<<< orphan*/ ) ; 
 int n_switches ; 
 TYPE_1__* switches ; 

__attribute__((used)) static inline void
process_marked_switches (void)
{
  int i;

  for (i = 0; i < n_switches; i++)
    if (switches[i].ordering == 1)
      {
	switches[i].ordering = 0;
	give_switch (i, 0);
      }
}