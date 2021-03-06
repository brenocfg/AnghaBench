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
struct TYPE_2__ {int /*<<< orphan*/  refcnt; } ;
struct sctp_endpoint {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_endpoint_destroy (struct sctp_endpoint*) ; 

void sctp_endpoint_put(struct sctp_endpoint *ep)
{
	if (atomic_dec_and_test(&ep->base.refcnt))
		sctp_endpoint_destroy(ep);
}