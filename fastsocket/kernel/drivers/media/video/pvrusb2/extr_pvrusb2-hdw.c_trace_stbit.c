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
 int /*<<< orphan*/  PVR2_TRACE_STBITS ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,char const*,char*) ; 

__attribute__((used)) static void trace_stbit(const char *name,int val)
{
	pvr2_trace(PVR2_TRACE_STBITS,
		   "State bit %s <-- %s",
		   name,(val ? "true" : "false"));
}