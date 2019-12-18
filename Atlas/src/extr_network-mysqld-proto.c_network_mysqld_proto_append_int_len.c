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
typedef  int guint64 ;
typedef  scalar_t__ gsize ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  g_string_append_c (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int network_mysqld_proto_append_int_len(GString *packet, guint64 num, gsize size) {
	gsize i;

	for (i = 0; i < size; i++) {
		g_string_append_c(packet, num & 0xff);
		num >>= 8;
	}

	return 0;
}