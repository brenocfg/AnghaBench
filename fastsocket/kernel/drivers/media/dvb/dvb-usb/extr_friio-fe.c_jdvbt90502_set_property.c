#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_frontend {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct dtv_property {int cmd; TYPE_1__ u; } ;

/* Variables and functions */
#define  DTV_CLEAR 131 
#define  DTV_DELIVERY_SYSTEM 130 
#define  DTV_FREQUENCY 129 
#define  DTV_TUNE 128 
 int EINVAL ; 
 int /*<<< orphan*/  SYS_ISDBT ; 

__attribute__((used)) static int jdvbt90502_set_property(struct dvb_frontend *fe,
				   struct dtv_property *tvp)
{
	int r = 0;

	switch (tvp->cmd) {
	case DTV_DELIVERY_SYSTEM:
		if (tvp->u.data != SYS_ISDBT)
			r = -EINVAL;
		break;
	case DTV_CLEAR:
	case DTV_TUNE:
	case DTV_FREQUENCY:
		break;
	default:
		r = -EINVAL;
	}
	return r;
}