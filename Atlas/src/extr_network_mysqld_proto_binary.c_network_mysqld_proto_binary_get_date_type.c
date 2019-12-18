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
typedef  int /*<<< orphan*/  network_packet ;
typedef  int /*<<< orphan*/  network_mysqld_type_t ;
struct TYPE_4__ {int month; int day; int hour; int min; int sec; int /*<<< orphan*/  nsec; int /*<<< orphan*/  year; } ;
typedef  TYPE_1__ network_mysqld_type_date_t ;
typedef  int guint8 ;
typedef  int /*<<< orphan*/  date ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ network_mysqld_proto_get_int16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ network_mysqld_proto_get_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ network_mysqld_proto_get_int8 (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ network_mysqld_type_set_date (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int network_mysqld_proto_binary_get_date_type(network_packet *packet, network_mysqld_type_t *type) {
	int err = 0;
	guint8 len;
	network_mysqld_type_date_t date;

	err = err || network_mysqld_proto_get_int8(packet, &len);

	/* check the valid lengths
	 */
	switch (len) {
	case 11: /* date + time + ms */
	case 7:  /* date + time ( ms is .0000 ) */
	case 4:  /* date ( time is 00:00:00 )*/
	case 0:  /* date == 0000-00-00 */
		break;
	default:
		return -1;
	}

	memset(&date, 0, sizeof(date));
	if (len > 0) {
		err = err || network_mysqld_proto_get_int16(packet, &date.year);
		err = err || network_mysqld_proto_get_int8(packet, &date.month);
		err = err || network_mysqld_proto_get_int8(packet, &date.day);
		
		if (len > 4) {
			err = err || network_mysqld_proto_get_int8(packet, &date.hour);
			err = err || network_mysqld_proto_get_int8(packet, &date.min);
			err = err || network_mysqld_proto_get_int8(packet, &date.sec);

			if (len > 7) {
				err = err || network_mysqld_proto_get_int32(packet, &date.nsec);
			}
		}
	}

	if (0 == err) {
		err = err || network_mysqld_type_set_date(type, &date);
	}

	return err ? -1 : 0;
}