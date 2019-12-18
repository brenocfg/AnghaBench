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
typedef  int /*<<< orphan*/  GTimeVal ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  g_get_current_time (int /*<<< orphan*/ *) ; 
 int g_string_get_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int g_string_get_current_time(GString *s) {
	GTimeVal gt;

	g_get_current_time(&gt);

	return g_string_get_time(s, &gt);
}