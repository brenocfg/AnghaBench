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
struct scsi_data_buffer {int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SCSI_MAX_SG_SEGMENTS ; 
 int __sg_alloc_table (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sg_free_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sg_alloc ; 
 int /*<<< orphan*/  scsi_sg_free ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int scsi_alloc_sgtable(struct scsi_data_buffer *sdb, int nents,
			      gfp_t gfp_mask)
{
	int ret;

	BUG_ON(!nents);

	ret = __sg_alloc_table(&sdb->table, nents, SCSI_MAX_SG_SEGMENTS,
			       gfp_mask, scsi_sg_alloc);
	if (unlikely(ret))
		__sg_free_table(&sdb->table, SCSI_MAX_SG_SEGMENTS,
				scsi_sg_free);

	return ret;
}