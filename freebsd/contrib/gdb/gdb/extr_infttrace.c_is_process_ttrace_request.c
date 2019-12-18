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
typedef  int /*<<< orphan*/  ttreq_t ;

/* Variables and functions */
 int IS_TTRACE_PROCREQ (int /*<<< orphan*/ ) ; 

int
is_process_ttrace_request (ttreq_t tt_request)
{
  return IS_TTRACE_PROCREQ (tt_request);
}