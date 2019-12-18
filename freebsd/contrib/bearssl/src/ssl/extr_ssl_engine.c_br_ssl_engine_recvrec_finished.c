#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int iomode; int ixa; int /*<<< orphan*/  ixc; } ;
typedef  TYPE_1__ br_ssl_engine_context ;

/* Variables and functions */
#define  BR_IO_IN 129 
#define  BR_IO_INOUT 128 

int
br_ssl_engine_recvrec_finished(const br_ssl_engine_context *rc)
{
	switch (rc->iomode) {
	case BR_IO_IN:
	case BR_IO_INOUT:
		return rc->ixc == 0 || rc->ixa < 5;
	default:
		return 1;
	}
}