#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  network_packet ;
struct TYPE_4__ {int sign; int hour; int min; int sec; int /*<<< orphan*/  nsec; int /*<<< orphan*/  days; } ;
typedef  TYPE_1__ network_mysqld_type_time_t ;
typedef  int /*<<< orphan*/  network_mysqld_type_t ;
typedef  int guint8 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ network_mysqld_proto_get_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ network_mysqld_proto_get_int8 (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ network_mysqld_type_set_time (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int network_mysqld_proto_binary_get_time_type(network_packet *packet, network_mysqld_type_t *type) {
	int err = 0;
	guint8 len;
	network_mysqld_type_time_t t;

	err = err || network_mysqld_proto_get_int8(packet, &len);

	/* check the valid lengths
	 */
	switch (len) {
	case 12: /* day + time + ms */
	case 8:  /* day + time ( ms is .0000 ) */
	case 0:  /* time == 00:00:00 */
		break;
	default:
		return -1;
	}

	memset(&t, 0, sizeof(t));
	if (len > 0) {
		err = err || network_mysqld_proto_get_int8(packet, &t.sign);
		err = err || network_mysqld_proto_get_int32(packet, &t.days);
		
		err = err || network_mysqld_proto_get_int8(packet, &t.hour);
		err = err || network_mysqld_proto_get_int8(packet, &t.min);
		err = err || network_mysqld_proto_get_int8(packet, &t.sec);

		if (len > 8) {
			err = err || network_mysqld_proto_get_int32(packet, &t.nsec);
		}
	}

	if (0 == err) {
		err = err || network_mysqld_type_set_time(type, &t);
	}

	return err ? -1 : 0;
}