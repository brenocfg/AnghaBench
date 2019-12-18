#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int capabilities; int max_packet_size; int charset; TYPE_3__* database; TYPE_3__* response; TYPE_3__* username; } ;
typedef  TYPE_1__ network_mysqld_auth_response ;
struct TYPE_5__ {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int CLIENT_PROTOCOL_41 ; 
 int /*<<< orphan*/  S (TYPE_3__*) ; 
 int /*<<< orphan*/  g_string_append_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_lenenc_string_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int network_mysqld_proto_append_auth_response(GString *packet, network_mysqld_auth_response *auth) {
	int i;

	if (!(auth->capabilities & CLIENT_PROTOCOL_41)) {
		network_mysqld_proto_append_int16(packet, auth->capabilities);
		network_mysqld_proto_append_int24(packet, auth->max_packet_size); /* max-allowed-packet */

		if (auth->username->len) g_string_append_len(packet, S(auth->username));
		network_mysqld_proto_append_int8(packet, 0x00); /* trailing \0 */

		if (auth->response->len) {
			g_string_append_len(packet, S(auth->response));
			network_mysqld_proto_append_int8(packet, 0x00); /* trailing \0 */
		}
	} else {
		network_mysqld_proto_append_int32(packet, auth->capabilities);
		network_mysqld_proto_append_int32(packet, auth->max_packet_size); /* max-allowed-packet */
		
		network_mysqld_proto_append_int8(packet, auth->charset); /* charset */

		for (i = 0; i < 23; i++) { /* filler */
			network_mysqld_proto_append_int8(packet, 0x00);
		}

		if (auth->username->len) g_string_append_len(packet, S(auth->username));
		network_mysqld_proto_append_int8(packet, 0x00); /* trailing \0 */

		/* scrambled password */
		network_mysqld_proto_append_lenenc_string_len(packet, S(auth->response));
		if (auth->database->len) {
			g_string_append_len(packet, S(auth->database));
			network_mysqld_proto_append_int8(packet, 0x00); /* trailing \0 */
		}
	}

	return 0;
}