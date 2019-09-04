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

const char *beforeunload_callback(int eventType, const void *reserved, void *userData)
{
#ifdef REPORT_RESULT
  return ""; // For test harness, don't show a confirmation dialog to not block and keep the test runner automated.
#else
  return "Do you really want to leave the page?";
#endif
}