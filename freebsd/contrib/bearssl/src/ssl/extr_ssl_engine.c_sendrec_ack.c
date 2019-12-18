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
struct TYPE_4__ {scalar_t__ oxb; scalar_t__ oxa; scalar_t__ oxc; } ;
typedef  TYPE_1__ br_ssl_engine_context ;

/* Variables and functions */
 int /*<<< orphan*/  make_ready_out (TYPE_1__*) ; 

__attribute__((used)) static void
sendrec_ack(br_ssl_engine_context *rc, size_t len)
{
	rc->oxb = (rc->oxa += len);
	if (rc->oxa == rc->oxc) {
		make_ready_out(rc);
	}
}