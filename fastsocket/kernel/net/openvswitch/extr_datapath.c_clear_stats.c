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
struct sw_flow {scalar_t__ byte_count; scalar_t__ packet_count; scalar_t__ tcp_flags; scalar_t__ used; } ;

/* Variables and functions */

__attribute__((used)) static void clear_stats(struct sw_flow *flow)
{
	flow->used = 0;
	flow->tcp_flags = 0;
	flow->packet_count = 0;
	flow->byte_count = 0;
}