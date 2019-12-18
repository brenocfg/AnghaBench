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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  ql_dbg (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ql_mask_match (int) ; 

void
ql_dump_buffer(uint32_t level, scsi_qla_host_t *vha, int32_t id,
	uint8_t *b, uint32_t size)
{
	uint32_t cnt;
	uint8_t c;

	if (!ql_mask_match(level))
		return;

	ql_dbg(level, vha, id, " 0   1   2   3   4   5   6   7   8   "
	    "9  Ah  Bh  Ch  Dh  Eh  Fh\n");
	ql_dbg(level, vha, id, "----------------------------------"
	    "----------------------------\n");

	ql_dbg(level, vha, id, " ");
	for (cnt = 0; cnt < size;) {
		c = *b++;
		printk("%02x", (uint32_t) c);
		cnt++;
		if (!(cnt % 16))
			printk("\n");
		else
			printk("  ");
	}
	if (cnt % 16)
		ql_dbg(level, vha, id, "\n");
}