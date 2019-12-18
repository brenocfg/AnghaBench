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
struct TYPE_2__ {int /*<<< orphan*/  bi_vblocknr; } ;
union nilfs_binfo {TYPE_1__ bi_v; } ;
struct nilfs_segsum_pointer {int dummy; } ;
struct nilfs_sc_info {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/ * nilfs_segctor_map_segsum_entry (struct nilfs_sc_info*,struct nilfs_segsum_pointer*,int) ; 

__attribute__((used)) static void nilfs_write_file_node_binfo(struct nilfs_sc_info *sci,
					struct nilfs_segsum_pointer *ssp,
					union nilfs_binfo *binfo)
{
	__le64 *vblocknr = nilfs_segctor_map_segsum_entry(
		sci, ssp, sizeof(*vblocknr));
	*vblocknr = binfo->bi_v.bi_vblocknr;
}