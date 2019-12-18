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
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/ * g_string_append_len (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_truncate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

GString * g_string_assign_len(GString *s, const char *str, gsize str_len) {
	g_string_truncate(s, 0);
	return g_string_append_len(s, str, str_len);
}