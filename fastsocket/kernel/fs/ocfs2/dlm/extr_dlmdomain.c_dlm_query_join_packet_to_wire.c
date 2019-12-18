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
struct dlm_query_join_packet {int dummy; } ;
union dlm_query_join_response {int /*<<< orphan*/  intval; struct dlm_query_join_packet packet; } ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dlm_query_join_packet_to_wire(struct dlm_query_join_packet *packet,
					  u32 *wire)
{
	union dlm_query_join_response response;

	response.packet = *packet;
	*wire = cpu_to_be32(response.intval);
}