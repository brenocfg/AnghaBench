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
typedef  int /*<<< orphan*/  t_history_entry ;
struct TYPE_2__ {int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int NUM_HISTORY_ENTRIES ; 
 TYPE_1__ history ; 
 int /*<<< orphan*/  history_load () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void history_default(void)
{
  int i;
  for(i=0; i < NUM_HISTORY_ENTRIES; i++)
    memset(&history.entries[i], 0, sizeof(t_history_entry));

  /* restore history */
  history_load();
}