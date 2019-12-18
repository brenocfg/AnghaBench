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
typedef  int /*<<< orphan*/  u16 ;
struct ocrdma_dev {int /*<<< orphan*/  sgid_lock; int /*<<< orphan*/ * sgid_tbl; } ;

/* Variables and functions */
 int OCRDMA_MAX_SGID ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,union ib_gid*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union ib_gid*,int) ; 
 int /*<<< orphan*/  memset (union ib_gid*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_build_sgid_mac (union ib_gid*,unsigned char*,int,int /*<<< orphan*/ ) ; 
 union ib_gid ocrdma_zero_sgid ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool ocrdma_add_sgid(struct ocrdma_dev *dev, unsigned char *mac_addr,
			    bool is_vlan, u16 vlan_id)
{
	int i;
	union ib_gid new_sgid;
	unsigned long flags;

	memset(&ocrdma_zero_sgid, 0, sizeof(union ib_gid));

	ocrdma_build_sgid_mac(&new_sgid, mac_addr, is_vlan, vlan_id);

	spin_lock_irqsave(&dev->sgid_lock, flags);
	for (i = 0; i < OCRDMA_MAX_SGID; i++) {
		if (!memcmp(&dev->sgid_tbl[i], &ocrdma_zero_sgid,
			    sizeof(union ib_gid))) {
			/* found free entry */
			memcpy(&dev->sgid_tbl[i], &new_sgid,
			       sizeof(union ib_gid));
			spin_unlock_irqrestore(&dev->sgid_lock, flags);
			return true;
		} else if (!memcmp(&dev->sgid_tbl[i], &new_sgid,
				   sizeof(union ib_gid))) {
			/* entry already present, no addition is required. */
			spin_unlock_irqrestore(&dev->sgid_lock, flags);
			return false;
		}
	}
	spin_unlock_irqrestore(&dev->sgid_lock, flags);
	return false;
}