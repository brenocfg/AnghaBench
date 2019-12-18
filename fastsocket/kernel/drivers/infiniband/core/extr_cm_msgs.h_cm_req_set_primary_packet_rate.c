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
typedef  int u8 ;
struct cm_req_msg {int /*<<< orphan*/  primary_offset88; } ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static inline void cm_req_set_primary_packet_rate(struct cm_req_msg *req_msg,
						  u8 rate)
{
	req_msg->primary_offset88 = cpu_to_be32(
				    (be32_to_cpu(req_msg->primary_offset88) &
				     0xFFFFFFC0) | (rate & 0x3F));
}