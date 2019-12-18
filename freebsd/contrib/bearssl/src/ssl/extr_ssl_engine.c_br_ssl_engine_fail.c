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
struct TYPE_3__ {scalar_t__ iomode; int err; } ;
typedef  TYPE_1__ br_ssl_engine_context ;

/* Variables and functions */
 scalar_t__ BR_IO_FAILED ; 

void
br_ssl_engine_fail(br_ssl_engine_context *rc, int err)
{
	if (rc->iomode != BR_IO_FAILED) {
		rc->iomode = BR_IO_FAILED;
		rc->err = err;
	}
}