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
struct osst_tape {int eod_frame_ppos; int first_data_ppos; int first_mark_ppos; int last_mark_ppos; int last_mark_lbn; scalar_t__ filemark_cnt; scalar_t__ frame_in_buffer; scalar_t__ frame_seq_number; scalar_t__ logical_blk_num; int /*<<< orphan*/ * header_cache; } ;
struct osst_request {int dummy; } ;
typedef  int /*<<< orphan*/  os_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int osst_write_header (struct osst_tape*,struct osst_request**,int) ; 

__attribute__((used)) static int osst_reset_header(struct osst_tape * STp, struct osst_request ** aSRpnt)
{
	if (STp->header_cache != NULL)
		memset(STp->header_cache, 0, sizeof(os_header_t));

	STp->logical_blk_num = STp->frame_seq_number = 0;
	STp->frame_in_buffer = 0;
	STp->eod_frame_ppos = STp->first_data_ppos = 0x0000000A;
	STp->filemark_cnt = 0;
	STp->first_mark_ppos = STp->last_mark_ppos = STp->last_mark_lbn = -1;
	return osst_write_header(STp, aSRpnt, 1);
}