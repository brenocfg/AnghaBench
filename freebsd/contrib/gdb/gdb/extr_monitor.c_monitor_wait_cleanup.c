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
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ in_monitor_wait ; 
 int /*<<< orphan*/  ofunc ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int timeout ; 

__attribute__((used)) static void
monitor_wait_cleanup (void *old_timeout)
{
  timeout = *(int *) old_timeout;
  signal (SIGINT, ofunc);
  in_monitor_wait = 0;
}