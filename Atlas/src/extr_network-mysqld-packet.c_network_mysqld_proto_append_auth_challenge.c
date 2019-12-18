#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int server_version; int charset; TYPE_1__* challenge; int /*<<< orphan*/  server_status; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  thread_id; scalar_t__ server_version_str; } ;
typedef  TYPE_2__ network_mysqld_auth_challenge ;
typedef  int guint ;
struct TYPE_4__ {scalar_t__ str; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  C (char*) ; 
 int /*<<< orphan*/  g_string_append (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  g_string_append_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  g_string_append_printf (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int8 (int /*<<< orphan*/ *,int) ; 

int network_mysqld_proto_append_auth_challenge(GString *packet, network_mysqld_auth_challenge *shake) {
	guint i;

	network_mysqld_proto_append_int8(packet, 0x0a);
	if (shake->server_version_str) {
		g_string_append(packet, shake->server_version_str);
	} else if (shake->server_version > 30000 && shake->server_version < 100000) {
		g_string_append_printf(packet, "%d.%02d.%02d", 
				shake->server_version / 10000,
				(shake->server_version % 10000) / 100,
				shake->server_version %   100
				);
	} else {
		g_string_append_len(packet, C("5.0.99"));
	}
	network_mysqld_proto_append_int8(packet, 0x00);
	network_mysqld_proto_append_int32(packet, shake->thread_id);
	if (shake->challenge->len) {
		g_string_append_len(packet, shake->challenge->str, 8);
	} else {
		g_string_append_len(packet, C("01234567"));
	}
	network_mysqld_proto_append_int8(packet, 0x00); /* filler */
	network_mysqld_proto_append_int16(packet, shake->capabilities);
	network_mysqld_proto_append_int8(packet, shake->charset);
	network_mysqld_proto_append_int16(packet, shake->server_status);

	for (i = 0; i < 13; i++) {
		network_mysqld_proto_append_int8(packet, 0x00);
	}

	if (shake->challenge->len) {
		g_string_append_len(packet, shake->challenge->str + 8, 12);
	} else {
		g_string_append_len(packet, C("890123456789"));
	}
	network_mysqld_proto_append_int8(packet, 0x00);
	
	return 0;
}