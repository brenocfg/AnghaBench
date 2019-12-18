#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network_packet ;
struct TYPE_5__ {int /*<<< orphan*/  is_null; } ;
typedef  TYPE_1__ network_mysqld_proto_field ;
typedef  size_t guint ;
struct TYPE_6__ {size_t len; TYPE_1__** pdata; } ;
typedef  TYPE_2__ GPtrArray ;

/* Variables and functions */
 scalar_t__ network_mysqld_proto_field_get (int /*<<< orphan*/ *,TYPE_1__*) ; 

int network_mysqld_proto_fields_get(network_packet *packet, GPtrArray *fields) {
	guint i;

	for (i = 0; i < fields->len; i++) {
		network_mysqld_proto_field *field = fields->pdata[i];

		if (!field->is_null) {
			if (network_mysqld_proto_field_get(packet, field)) return -1;
		}
	}

	return 0;
}