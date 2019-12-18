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
typedef  int /*<<< orphan*/  network_packet ;
typedef  int /*<<< orphan*/  network_mysqld_type_t ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (int /*<<< orphan*/ *) ; 
 scalar_t__ network_mysqld_proto_get_lenenc_gstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_type_set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int network_mysqld_proto_binary_get_string_type(network_packet *packet, network_mysqld_type_t *type) {
	GString *str;
	int err = 0;

	str = g_string_new(NULL);

	err = err || network_mysqld_proto_get_lenenc_gstring(packet, str);

	network_mysqld_type_set_string(type, S(str));

	g_string_free(str, TRUE);

	return err ? -1 : 0;
}