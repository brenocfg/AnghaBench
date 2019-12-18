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
typedef  int guint ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  g_string_append_c (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  g_string_append_printf (int /*<<< orphan*/ *,char*,int) ; 

void append_key(guint *key, guint *value, GString *str) {
	g_string_append_c(str, ',');
	guint sum = *key;

	g_string_append_printf(str, "%u", sum & 0x000000FF);

	guint i;
	for (i = 1; i <= 3; ++i) {
		sum >>= 8;
		g_string_append_printf(str, ".%u", sum & 0x000000FF);
	}
}