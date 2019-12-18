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
struct blkio_group {int plid; } ;
typedef  enum blkio_policy_id { ____Placeholder_blkio_policy_id } blkio_policy_id ;

/* Variables and functions */
 int BLKIOFILE_POLICY (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool cftype_blkg_same_policy(struct cftype *cft,
			struct blkio_group *blkg)
{
	enum blkio_policy_id plid = BLKIOFILE_POLICY(cft->private);

	if (blkg->plid == plid)
		return 1;

	return 0;
}