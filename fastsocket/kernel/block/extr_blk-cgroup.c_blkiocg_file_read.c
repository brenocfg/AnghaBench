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
struct seq_file {int dummy; } ;
struct cgroup {int dummy; } ;
struct cftype {int /*<<< orphan*/  private; } ;
struct blkio_cgroup {int dummy; } ;
typedef  enum blkio_policy_id { ____Placeholder_blkio_policy_id } blkio_policy_id ;

/* Variables and functions */
 int BLKIOFILE_ATTR (int /*<<< orphan*/ ) ; 
 int BLKIOFILE_POLICY (int /*<<< orphan*/ ) ; 
#define  BLKIO_POLICY_PROP 134 
#define  BLKIO_POLICY_THROTL 133 
#define  BLKIO_PROP_weight_device 132 
#define  BLKIO_THROTL_read_bps_device 131 
#define  BLKIO_THROTL_read_iops_device 130 
#define  BLKIO_THROTL_write_bps_device 129 
#define  BLKIO_THROTL_write_iops_device 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  blkio_read_policy_node_files (struct cftype*,struct blkio_cgroup*,struct seq_file*) ; 
 struct blkio_cgroup* cgroup_to_blkio_cgroup (struct cgroup*) ; 

__attribute__((used)) static int blkiocg_file_read(struct cgroup *cgrp, struct cftype *cft,
				struct seq_file *m)
{
	struct blkio_cgroup *blkcg;
	enum blkio_policy_id plid = BLKIOFILE_POLICY(cft->private);
	int name = BLKIOFILE_ATTR(cft->private);

	blkcg = cgroup_to_blkio_cgroup(cgrp);

	switch(plid) {
	case BLKIO_POLICY_PROP:
		switch(name) {
		case BLKIO_PROP_weight_device:
			blkio_read_policy_node_files(cft, blkcg, m);
			return 0;
		default:
			BUG();
		}
		break;
	case BLKIO_POLICY_THROTL:
		switch(name){
		case BLKIO_THROTL_read_bps_device:
		case BLKIO_THROTL_write_bps_device:
		case BLKIO_THROTL_read_iops_device:
		case BLKIO_THROTL_write_iops_device:
			blkio_read_policy_node_files(cft, blkcg, m);
			return 0;
		default:
			BUG();
		}
		break;
	default:
		BUG();
	}

	return 0;
}