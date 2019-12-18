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

/* Variables and functions */
 scalar_t__ timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_mp ; 
 scalar_t__ timeout_mp_id ; 
 int /*<<< orphan*/  untimeout (scalar_t__) ; 

void
reschedule_timeout_mp(void)
{
  if (timeout_mp_id)
    untimeout(timeout_mp_id);
  timeout_mp_id = timeout(0, timeout_mp, NULL);
}