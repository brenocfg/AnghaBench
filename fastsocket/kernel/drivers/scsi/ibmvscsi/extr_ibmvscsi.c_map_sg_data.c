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
typedef  void* u64 ;
struct TYPE_2__ {int len; scalar_t__ va; scalar_t__ key; } ;
struct srp_indirect_buf {struct srp_direct_buf* desc_list; TYPE_1__ table_desc; void* len; } ;
struct srp_event_struct {struct srp_direct_buf* ext_list; scalar_t__ ext_list_token; } ;
struct srp_direct_buf {int dummy; } ;
struct srp_cmd {scalar_t__ add_data; } ;
struct scsi_cmnd {int /*<<< orphan*/  device; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_CMO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int MAX_INDIRECT_BUFS ; 
 int SG_ALL ; 
 scalar_t__ dma_alloc_coherent (struct device*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firmware_has_feature (int /*<<< orphan*/ ) ; 
 void* map_sg_list (struct scsi_cmnd*,int,struct srp_direct_buf*) ; 
 int /*<<< orphan*/  memcpy (struct srp_direct_buf*,struct srp_direct_buf*,int) ; 
 int scsi_dma_map (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_srp_direction (struct scsi_cmnd*,struct srp_cmd*,int) ; 

__attribute__((used)) static int map_sg_data(struct scsi_cmnd *cmd,
		       struct srp_event_struct *evt_struct,
		       struct srp_cmd *srp_cmd, struct device *dev)
{

	int sg_mapped;
	u64 total_length = 0;
	struct srp_direct_buf *data =
		(struct srp_direct_buf *) srp_cmd->add_data;
	struct srp_indirect_buf *indirect =
		(struct srp_indirect_buf *) data;

	sg_mapped = scsi_dma_map(cmd);
	if (!sg_mapped)
		return 1;
	else if (sg_mapped < 0)
		return 0;

	set_srp_direction(cmd, srp_cmd, sg_mapped);

	/* special case; we can use a single direct descriptor */
	if (sg_mapped == 1) {
		map_sg_list(cmd, sg_mapped, data);
		return 1;
	}

	indirect->table_desc.va = 0;
	indirect->table_desc.len = sg_mapped * sizeof(struct srp_direct_buf);
	indirect->table_desc.key = 0;

	if (sg_mapped <= MAX_INDIRECT_BUFS) {
		total_length = map_sg_list(cmd, sg_mapped,
					   &indirect->desc_list[0]);
		indirect->len = total_length;
		return 1;
	}

	/* get indirect table */
	if (!evt_struct->ext_list) {
		evt_struct->ext_list = (struct srp_direct_buf *)
			dma_alloc_coherent(dev,
					   SG_ALL * sizeof(struct srp_direct_buf),
					   &evt_struct->ext_list_token, 0);
		if (!evt_struct->ext_list) {
			if (!firmware_has_feature(FW_FEATURE_CMO))
				sdev_printk(KERN_ERR, cmd->device,
				            "Can't allocate memory "
				            "for indirect table\n");
			scsi_dma_unmap(cmd);
			return 0;
		}
	}

	total_length = map_sg_list(cmd, sg_mapped, evt_struct->ext_list);

	indirect->len = total_length;
	indirect->table_desc.va = evt_struct->ext_list_token;
	indirect->table_desc.len = sg_mapped * sizeof(indirect->desc_list[0]);
	memcpy(indirect->desc_list, evt_struct->ext_list,
	       MAX_INDIRECT_BUFS * sizeof(struct srp_direct_buf));
 	return 1;
}