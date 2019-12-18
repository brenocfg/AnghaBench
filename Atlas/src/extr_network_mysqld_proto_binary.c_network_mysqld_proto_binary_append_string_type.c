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
typedef  int /*<<< orphan*/  network_mysqld_type_t ;
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 scalar_t__ network_mysqld_proto_append_lenenc_string_len (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ network_mysqld_type_get_string_const (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int network_mysqld_proto_binary_append_string_type(GString *packet, network_mysqld_type_t *type) {
	const char *s;
	gsize s_len;
	int err = 0;

	err = err || network_mysqld_type_get_string_const(type, &s, &s_len);
	err = err || network_mysqld_proto_append_lenenc_string_len(packet, s, s_len);

	return err ? -1 : 0;
}