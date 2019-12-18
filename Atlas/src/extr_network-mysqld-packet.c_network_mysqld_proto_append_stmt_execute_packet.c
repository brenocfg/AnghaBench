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
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ is_null; scalar_t__ type; } ;
typedef  TYPE_1__ network_mysqld_type_t ;
struct TYPE_18__ {TYPE_14__* params; scalar_t__ new_params_bound; int /*<<< orphan*/  iteration_count; scalar_t__ flags; int /*<<< orphan*/  stmt_id; } ;
typedef  TYPE_2__ network_mysqld_stmt_execute_packet_t ;
typedef  int /*<<< orphan*/  guint16 ;
typedef  int guint ;
typedef  int gsize ;
struct TYPE_19__ {int* str; int /*<<< orphan*/  len; } ;
struct TYPE_16__ {int len; } ;
typedef  TYPE_3__ GString ;

/* Variables and functions */
 scalar_t__ COM_STMT_EXECUTE ; 
 int /*<<< orphan*/  S (TYPE_3__*) ; 
 TYPE_1__* g_ptr_array_index (TYPE_14__*,int) ; 
 int /*<<< orphan*/  g_string_append_len (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* g_string_sized_new (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int16 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int32 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int8 (TYPE_3__*,scalar_t__) ; 
 scalar_t__ network_mysqld_proto_binary_append_type (TYPE_3__*,TYPE_1__*) ; 

int network_mysqld_proto_append_stmt_execute_packet(GString *packet,
		network_mysqld_stmt_execute_packet_t *stmt_execute_packet,
		guint param_count) {
	gsize nul_bits_len;
	GString *nul_bits;
	guint i;
	int err = 0;

	nul_bits_len = (param_count + 7) / 8;
	nul_bits = g_string_sized_new(nul_bits_len);
	memset(nul_bits->str, 0, nul_bits->len); /* set it all to zero */

	for (i = 0; i < param_count; i++) {
		network_mysqld_type_t *param = g_ptr_array_index(stmt_execute_packet->params, i);

		if (param->is_null) {
			nul_bits->str[i / 8] |= 1 << (i % 8);
		}
	}

	network_mysqld_proto_append_int8(packet, COM_STMT_EXECUTE);
	network_mysqld_proto_append_int32(packet, stmt_execute_packet->stmt_id);
	network_mysqld_proto_append_int8(packet, stmt_execute_packet->flags);
	network_mysqld_proto_append_int32(packet, stmt_execute_packet->iteration_count);
	g_string_append_len(packet, S(nul_bits));
	network_mysqld_proto_append_int8(packet, stmt_execute_packet->new_params_bound);

	if (stmt_execute_packet->new_params_bound) {
		for (i = 0; i < stmt_execute_packet->params->len; i++) {
			network_mysqld_type_t *param = g_ptr_array_index(stmt_execute_packet->params, i);

			network_mysqld_proto_append_int16(packet, (guint16)param->type);
		}
		for (i = 0; 0 == err && i < stmt_execute_packet->params->len; i++) {
			network_mysqld_type_t *param = g_ptr_array_index(stmt_execute_packet->params, i);
			
			if (!param->is_null) {
				err = err || network_mysqld_proto_binary_append_type(packet, param);
			}
		}
	}

	return err ? -1 : 0;
}