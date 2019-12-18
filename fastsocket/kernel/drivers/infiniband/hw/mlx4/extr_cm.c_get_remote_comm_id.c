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
typedef  int /*<<< orphan*/  u32 ;
struct ib_mad {int dummy; } ;
struct cm_generic_msg {int /*<<< orphan*/  remote_comm_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_remote_comm_id(struct ib_mad *mad)
{
	struct cm_generic_msg *msg = (struct cm_generic_msg *)mad;

	return be32_to_cpu(msg->remote_comm_id);
}