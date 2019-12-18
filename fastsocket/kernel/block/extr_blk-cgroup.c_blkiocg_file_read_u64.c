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
typedef  int /*<<< orphan*/  u64 ;
struct cgroup {int dummy; } ;
struct cftype {int /*<<< orphan*/  private; } ;
struct blkio_cgroup {int /*<<< orphan*/  weight; } ;
typedef  enum blkio_policy_id { ____Placeholder_blkio_policy_id } blkio_policy_id ;

/* Variables and functions */
 int BLKIOFILE_ATTR (int /*<<< orphan*/ ) ; 
 int BLKIOFILE_POLICY (int /*<<< orphan*/ ) ; 
#define  BLKIO_POLICY_PROP 129 
#define  BLKIO_PROP_weight 128 
 int /*<<< orphan*/  BUG () ; 
 struct blkio_cgroup* cgroup_to_blkio_cgroup (struct cgroup*) ; 

__attribute__((used)) static u64 blkiocg_file_read_u64 (struct cgroup *cgrp, struct cftype *cft) {
	struct blkio_cgroup *blkcg;
	enum blkio_policy_id plid = BLKIOFILE_POLICY(cft->private);
	int name = BLKIOFILE_ATTR(cft->private);

	blkcg = cgroup_to_blkio_cgroup(cgrp);

	switch(plid) {
	case BLKIO_POLICY_PROP:
		switch(name) {
		case BLKIO_PROP_weight:
			return (u64)blkcg->weight;
		}
		break;
	default:
		BUG();
	}
	return 0;
}