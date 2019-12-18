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

/* Variables and functions */
 int /*<<< orphan*/  SCSI_MAX_SG_SEGMENTS ; 
 int /*<<< orphan*/  __sg_free_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sg_free ; 

__attribute__((used)) static void scsi_free_sgtable(struct scsi_data_buffer *sdb)
{
	__sg_free_table(&sdb->table, SCSI_MAX_SG_SEGMENTS, scsi_sg_free);
}