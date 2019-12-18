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
struct TYPE_6__ {unsigned int raid_disks; int /*<<< orphan*/  layout; } ;
struct raid_set {TYPE_4__* dev; TYPE_2__ md; TYPE_1__* raid_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  sb_page; } ;
struct TYPE_8__ {TYPE_3__ rdev; } ;
struct TYPE_5__ {int level; unsigned int parity_devs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  In_sync ; 
 unsigned int raid10_md_layout_to_copies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int validate_raid_redundancy(struct raid_set *rs)
{
	unsigned i, rebuild_cnt = 0;
	unsigned rebuilds_per_group = 0, copies, d;

	for (i = 0; i < rs->md.raid_disks; i++)
		if (!test_bit(In_sync, &rs->dev[i].rdev.flags) ||
		    !rs->dev[i].rdev.sb_page)
			rebuild_cnt++;

	switch (rs->raid_type->level) {
	case 1:
		if (rebuild_cnt >= rs->md.raid_disks)
			goto too_many;
		break;
	case 4:
	case 5:
	case 6:
		if (rebuild_cnt > rs->raid_type->parity_devs)
			goto too_many;
		break;
	case 10:
		copies = raid10_md_layout_to_copies(rs->md.layout);
		if (rebuild_cnt < copies)
			break;

		/*
		 * It is possible to have a higher rebuild count for RAID10,
		 * as long as the failed devices occur in different mirror
		 * groups (i.e. different stripes).
		 *
		 * Right now, we only allow for "near" copies.  When other
		 * formats are added, we will have to check those too.
		 *
		 * When checking "near" format, make sure no adjacent devices
		 * have failed beyond what can be handled.  In addition to the
		 * simple case where the number of devices is a multiple of the
		 * number of copies, we must also handle cases where the number
		 * of devices is not a multiple of the number of copies.
		 * E.g.    dev1 dev2 dev3 dev4 dev5
		 *          A    A    B    B    C
		 *          C    D    D    E    E
		 */
		for (i = 0; i < rs->md.raid_disks * copies; i++) {
			if (!(i % copies))
				rebuilds_per_group = 0;
			d = i % rs->md.raid_disks;
			if ((!rs->dev[d].rdev.sb_page ||
			     !test_bit(In_sync, &rs->dev[d].rdev.flags)) &&
			    (++rebuilds_per_group >= copies))
				goto too_many;
		}
		break;
	default:
		if (rebuild_cnt)
			return -EINVAL;
	}

	return 0;

too_many:
	return -EINVAL;
}