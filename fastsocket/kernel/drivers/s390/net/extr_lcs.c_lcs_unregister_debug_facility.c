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
 int /*<<< orphan*/  debug_unregister (scalar_t__) ; 
 scalar_t__ lcs_dbf_setup ; 
 scalar_t__ lcs_dbf_trace ; 

__attribute__((used)) static void
lcs_unregister_debug_facility(void)
{
	if (lcs_dbf_setup)
		debug_unregister(lcs_dbf_setup);
	if (lcs_dbf_trace)
		debug_unregister(lcs_dbf_trace);
}