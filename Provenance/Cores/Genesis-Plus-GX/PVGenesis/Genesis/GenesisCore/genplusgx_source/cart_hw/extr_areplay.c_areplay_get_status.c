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
struct TYPE_2__ {int status; scalar_t__ enabled; } ;

/* Variables and functions */
 TYPE_1__ action_replay ; 

int areplay_get_status(void)
{
  if (action_replay.enabled)
  {
    return action_replay.status;
  }

  return -1;
}