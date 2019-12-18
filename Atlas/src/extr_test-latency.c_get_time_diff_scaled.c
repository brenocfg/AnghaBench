#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_4__ {int /*<<< orphan*/ * str; } ;
typedef  int /*<<< orphan*/  GTimeVal ;
typedef  TYPE_1__ GString ;

/* Variables and functions */
 double TIME_DIFF_US (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_string_printf (TYPE_1__*,char*,double) ; 

gchar * get_time_diff_scaled(GTimeVal *t1, GTimeVal *t2, GString *str) {
	double query_time_us;
	double query_time;
	char *query_time_format = NULL;

	query_time_us = TIME_DIFF_US(t1, t2);

	query_time = query_time_us / 1000.0;
	query_time_format = "%0.3f";

	g_string_printf(str, query_time_format, query_time);

	return str->str;
}