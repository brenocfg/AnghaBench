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
struct cm_generic_msg {int /*<<< orphan*/  local_comm_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_local_comm_id(struct ib_mad *mad, u32 cm_id)
{
	struct cm_generic_msg *msg = (struct cm_generic_msg *)mad;
	msg->local_comm_id = cpu_to_be32(cm_id);
}