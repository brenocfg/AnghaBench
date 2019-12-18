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
typedef  union ib_gid {int dummy; } ib_gid ;
struct ib_mad {int dummy; } ;
struct ib_device {int dummy; } ;
struct cm_req_msg {union ib_gid primary_path_sgid; } ;

/* Variables and functions */

__attribute__((used)) static union ib_gid gid_from_req_msg(struct ib_device *ibdev, struct ib_mad *mad)
{
	struct cm_req_msg *msg = (struct cm_req_msg *)mad;

	return msg->primary_path_sgid;
}