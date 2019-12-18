#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  interface_id; } ;
union ib_gid {TYPE_1__ global; } ;
typedef  scalar_t__ u32 ;
struct id_map_entry {int slave_id; int /*<<< orphan*/  sl_cm_id; } ;
struct TYPE_4__ {scalar_t__ attr_id; } ;
struct ib_mad {TYPE_2__ mad_hdr; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CM_DREP_ATTR_ID ; 
 scalar_t__ CM_DREQ_ATTR_ID ; 
 scalar_t__ CM_REJ_ATTR_ID ; 
 scalar_t__ CM_REQ_ATTR_ID ; 
 int ENOENT ; 
 scalar_t__ get_remote_comm_id (struct ib_mad*) ; 
 union ib_gid gid_from_req_msg (struct ib_device*,struct ib_mad*) ; 
 int /*<<< orphan*/  id_map_find_del (struct ib_device*,int) ; 
 struct id_map_entry* id_map_get (struct ib_device*,int*,int,int) ; 
 int mlx4_ib_find_real_gid (struct ib_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_ib_warn (struct ib_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  schedule_delayed (struct ib_device*,struct id_map_entry*) ; 
 int /*<<< orphan*/  set_remote_comm_id (struct ib_mad*,int /*<<< orphan*/ ) ; 

int mlx4_ib_demux_cm_handler(struct ib_device *ibdev, int port, int *slave,
							     struct ib_mad *mad)
{
	u32 pv_cm_id;
	struct id_map_entry *id;

	if (mad->mad_hdr.attr_id == CM_REQ_ATTR_ID) {
		union ib_gid gid;

		gid = gid_from_req_msg(ibdev, mad);
		*slave = mlx4_ib_find_real_gid(ibdev, port, gid.global.interface_id);
		if (*slave < 0) {
			mlx4_ib_warn(ibdev, "failed matching slave_id by gid (0x%llx)\n",
					gid.global.interface_id);
			return -ENOENT;
		}
		return 0;
	}

	pv_cm_id = get_remote_comm_id(mad);
	id = id_map_get(ibdev, (int *)&pv_cm_id, -1, -1);

	if (!id) {
		pr_debug("Couldn't find an entry for pv_cm_id 0x%x\n", pv_cm_id);
		return -ENOENT;
	}

	*slave = id->slave_id;
	set_remote_comm_id(mad, id->sl_cm_id);

	if (mad->mad_hdr.attr_id == CM_DREQ_ATTR_ID)
		schedule_delayed(ibdev, id);
	else if (mad->mad_hdr.attr_id == CM_REJ_ATTR_ID ||
			mad->mad_hdr.attr_id == CM_DREP_ATTR_ID) {
		id_map_find_del(ibdev, (int) pv_cm_id);
	}

	return 0;
}