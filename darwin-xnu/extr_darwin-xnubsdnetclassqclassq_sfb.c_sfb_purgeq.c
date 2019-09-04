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
typedef  scalar_t__ u_int32_t ;
struct sfb {TYPE_1__* sfb_ifp; } ;
typedef  int /*<<< orphan*/  pktsched_pkt_t ;
typedef  int /*<<< orphan*/  class_queue_t ;
struct TYPE_2__ {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_CONVERT_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pktsched_free_pkt (int /*<<< orphan*/ *) ; 
 scalar_t__ pktsched_get_pkt_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sfb_getq_flow (struct sfb*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
sfb_purgeq(struct sfb *sp, class_queue_t *q, u_int32_t flow, u_int32_t *packets,
    u_int32_t *bytes)
{
	u_int32_t cnt = 0, len = 0;
	pktsched_pkt_t pkt;

	IFCQ_CONVERT_LOCK(&sp->sfb_ifp->if_snd);
	while (sfb_getq_flow(sp, q, flow, TRUE, &pkt) != NULL) {
		cnt++;
		len += pktsched_get_pkt_len(&pkt);
		pktsched_free_pkt(&pkt);
	}

	if (packets != NULL)
		*packets = cnt;
	if (bytes != NULL)
		*bytes = len;
}