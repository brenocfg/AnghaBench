#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rndis_filter_packet {int /*<<< orphan*/  completion_ctx; int /*<<< orphan*/  (* completion ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rndis_filter_send_completion(void *ctx)
{
	struct rndis_filter_packet *filter_pkt = ctx;

	/* Pass it back to the original handler */
	filter_pkt->completion(filter_pkt->completion_ctx);
}