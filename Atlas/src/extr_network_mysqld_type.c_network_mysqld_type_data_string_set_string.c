#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ network_mysqld_type_t ;
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  g_string_assign_len (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_sized_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int network_mysqld_type_data_string_set_string(network_mysqld_type_t *type, const char *src, gsize src_len) {
	GString *dst;

	if (NULL == type->data) {
		type->data = g_string_sized_new(src_len);
	}

	dst = type->data;

	g_string_assign_len(dst, src, src_len);
	
	return 0;
}