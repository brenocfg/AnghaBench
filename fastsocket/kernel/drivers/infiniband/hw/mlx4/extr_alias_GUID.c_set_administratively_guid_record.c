#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx4_sriov_alias_guid_info_rec_det {int /*<<< orphan*/  status; int /*<<< orphan*/  all_recs; int /*<<< orphan*/  guid_indexes; } ;
struct TYPE_7__ {TYPE_4__* ports_guid; } ;
struct TYPE_5__ {TYPE_3__ alias_guid; } ;
struct mlx4_ib_dev {TYPE_1__ sriov; } ;
struct TYPE_8__ {TYPE_2__* all_rec_per_port; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; int /*<<< orphan*/  all_recs; int /*<<< orphan*/  guid_indexes; } ;

/* Variables and functions */
 int GUID_REC_SIZE ; 
 int NUM_ALIAS_GUID_IN_REC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_administratively_guid_record(struct mlx4_ib_dev *dev, int port,
					     int rec_index,
					     struct mlx4_sriov_alias_guid_info_rec_det *rec_det)
{
	dev->sriov.alias_guid.ports_guid[port].all_rec_per_port[rec_index].guid_indexes =
		rec_det->guid_indexes;
	memcpy(dev->sriov.alias_guid.ports_guid[port].all_rec_per_port[rec_index].all_recs,
	       rec_det->all_recs, NUM_ALIAS_GUID_IN_REC * GUID_REC_SIZE);
	dev->sriov.alias_guid.ports_guid[port].all_rec_per_port[rec_index].status =
		rec_det->status;
}