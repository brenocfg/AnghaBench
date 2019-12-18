#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* ax25_dev; } ;
typedef  TYPE_3__ ax25_cb ;
struct TYPE_5__ {int /*<<< orphan*/  slave; } ;
struct TYPE_6__ {int* values; TYPE_1__ dama; } ;

/* Variables and functions */
#define  AX25_PROTO_DAMA_SLAVE 130 
#define  AX25_PROTO_STD_DUPLEX 129 
#define  AX25_PROTO_STD_SIMPLEX 128 
 size_t AX25_VALUES_PROTOCOL ; 
 int /*<<< orphan*/  ax25_std_t1timer_expiry (TYPE_3__*) ; 

__attribute__((used)) static void ax25_t1timer_expiry(unsigned long param)
{
	ax25_cb *ax25 = (ax25_cb *)param;

	switch (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) {
	case AX25_PROTO_STD_SIMPLEX:
	case AX25_PROTO_STD_DUPLEX:
		ax25_std_t1timer_expiry(ax25);
		break;

#ifdef CONFIG_AX25_DAMA_SLAVE
	case AX25_PROTO_DAMA_SLAVE:
		if (!ax25->ax25_dev->dama.slave)
			ax25_std_t1timer_expiry(ax25);
		break;
#endif
	}
}