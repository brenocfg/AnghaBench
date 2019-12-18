#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ offset; TYPE_1__* data; } ;
typedef  TYPE_2__ network_packet ;
struct TYPE_19__ {int capabilities; int max_packet_size; int /*<<< orphan*/  response; int /*<<< orphan*/  username; TYPE_12__* database; int /*<<< orphan*/  charset; } ;
typedef  TYPE_3__ network_mysqld_auth_response ;
typedef  int guint16 ;
struct TYPE_17__ {scalar_t__ len; } ;
struct TYPE_16__ {int len; char* str; } ;

/* Variables and functions */
 int CLIENT_PROTOCOL_41 ; 
 int CLIENT_SECURE_CONNECTION ; 
 scalar_t__ network_mysqld_proto_get_gstring (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ network_mysqld_proto_get_gstring_len (TYPE_2__*,scalar_t__,TYPE_12__*) ; 
 scalar_t__ network_mysqld_proto_get_int16 (TYPE_2__*,int*) ; 
 scalar_t__ network_mysqld_proto_get_int24 (TYPE_2__*,int*) ; 
 scalar_t__ network_mysqld_proto_get_int32 (TYPE_2__*,int*) ; 
 scalar_t__ network_mysqld_proto_get_int8 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ network_mysqld_proto_get_lenenc_gstring (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ network_mysqld_proto_peek_int16 (TYPE_2__*,int*) ; 
 scalar_t__ network_mysqld_proto_skip (TYPE_2__*,int) ; 

int network_mysqld_proto_get_auth_response(network_packet *packet, network_mysqld_auth_response *auth) {
	int err = 0;
	guint16 l_cap;
	/* extract the default db from it */

	/*
	 * @\0\0\1
	 *  \215\246\3\0 - client-flags
	 *  \0\0\0\1     - max-packet-len
	 *  \10          - charset-num
	 *  \0\0\0\0
	 *  \0\0\0\0
	 *  \0\0\0\0
	 *  \0\0\0\0
	 *  \0\0\0\0
	 *  \0\0\0       - fillers
	 *  root\0       - username
	 *  \24          - len of the scrambled buf
	 *    ~    \272 \361 \346
	 *    \211 \353 D    \351
	 *    \24  \243 \223 \257
	 *    \0   ^    \n   \254
	 *    t    \347 \365 \244
	 *  
	 *  world\0
	 */


	/* 4.0 uses 2 byte, 4.1+ uses 4 bytes, but the proto-flag is in the lower 2 bytes */
	err = err || network_mysqld_proto_peek_int16(packet, &l_cap);
	if (err) return -1;

	if (l_cap & CLIENT_PROTOCOL_41) {
		err = err || network_mysqld_proto_get_int32(packet, &auth->capabilities);
		err = err || network_mysqld_proto_get_int32(packet, &auth->max_packet_size);
		err = err || network_mysqld_proto_get_int8(packet, &auth->charset);

		err = err || network_mysqld_proto_skip(packet, 23);
	
		err = err || network_mysqld_proto_get_gstring(packet, auth->username);
		if (auth->capabilities & CLIENT_SECURE_CONNECTION) {
			err = err || network_mysqld_proto_get_lenenc_gstring(packet, auth->response);
		} else {
			err = err || network_mysqld_proto_get_gstring(packet, auth->response);
		}

		if (packet->offset != packet->data->len) {
			/* database is optional and may include a trailing \0 char */
			err = err || network_mysqld_proto_get_gstring_len(packet, packet->data->len - packet->offset, auth->database);

			if (auth->database->len > 0 && 
			    (auth->database->str[auth->database->len - 1] == '\0')) {
				auth->database->len--;
			}
		}
	} else {
		err = err || network_mysqld_proto_get_int16(packet, &l_cap);
		err = err || network_mysqld_proto_get_int24(packet, &auth->max_packet_size);
		err = err || network_mysqld_proto_get_gstring(packet, auth->username);
		/* there may be no password sent */
		if (packet->data->len != packet->offset) {
			err = err || network_mysqld_proto_get_gstring(packet, auth->response);
		}

		if (!err) {
			auth->capabilities = l_cap;
		}
	}

	return err ? -1 : 0;
}