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
struct cftype {int /*<<< orphan*/  private; } ;
struct blkio_policy_node {int plid; int fileid; } ;
typedef  enum blkio_policy_id { ____Placeholder_blkio_policy_id } blkio_policy_id ;

/* Variables and functions */
 int BLKIOFILE_ATTR (int /*<<< orphan*/ ) ; 
 int BLKIOFILE_POLICY (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool pn_matches_cftype(struct cftype *cft,
			struct blkio_policy_node *pn)
{
	enum blkio_policy_id plid = BLKIOFILE_POLICY(cft->private);
	int fileid = BLKIOFILE_ATTR(cft->private);

	return (plid == pn->plid && fileid == pn->fileid);
}