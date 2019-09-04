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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static boolean_t
memorystatus_avail_pages_below_critical(void)
{
#if CONFIG_EMBEDDED
	return (memorystatus_available_pages <= memorystatus_available_pages_critical);
#else /* CONFIG_EMBEDDED */
	return FALSE;
#endif /* CONFIG_EMBEDDED */
}