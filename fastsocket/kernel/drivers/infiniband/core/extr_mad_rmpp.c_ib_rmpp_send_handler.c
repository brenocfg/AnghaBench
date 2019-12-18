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
struct ib_mad_send_wc {TYPE_1__* send_buf; } ;
struct TYPE_2__ {scalar_t__* context; scalar_t__ ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_destroy_ah (scalar_t__) ; 
 int /*<<< orphan*/  ib_free_send_mad (TYPE_1__*) ; 

void ib_rmpp_send_handler(struct ib_mad_send_wc *mad_send_wc)
{
	if (mad_send_wc->send_buf->context[0] == mad_send_wc->send_buf->ah)
		ib_destroy_ah(mad_send_wc->send_buf->ah);
	ib_free_send_mad(mad_send_wc->send_buf);
}