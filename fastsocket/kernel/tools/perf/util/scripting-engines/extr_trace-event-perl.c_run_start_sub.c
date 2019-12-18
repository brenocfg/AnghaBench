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
 int G_DISCARD ; 
 int G_NOARGS ; 
 int /*<<< orphan*/  PUSHMARK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SP ; 
 int /*<<< orphan*/  call_pv (char*,int) ; 
 int /*<<< orphan*/  dSP ; 
 scalar_t__ get_cv (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_start_sub(void)
{
	dSP; /* access to Perl stack */
	PUSHMARK(SP);

	if (get_cv("main::trace_begin", 0))
		call_pv("main::trace_begin", G_DISCARD | G_NOARGS);
}