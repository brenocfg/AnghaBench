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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int bc_ver; scalar_t__ shmem_base; } ;
struct bnx2x {TYPE_1__ common; int /*<<< orphan*/  dev; } ;
typedef  int __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,...) ; 
 scalar_t__ BP_NOMCP (struct bnx2x*) ; 
 scalar_t__ BP_PATH (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ MCP_A_REG_MCPR_SCRATCH ; 
 scalar_t__ MCP_REG_MCPR_CPU_PROGRAM_COUNTER ; 
 scalar_t__ MCP_REG_MCPR_SCRATCH ; 
 scalar_t__ MFW_TRACE_SIGNATURE ; 
 scalar_t__ REG_RD (struct bnx2x*,scalar_t__) ; 
 scalar_t__ SHMEM2_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int htonl (scalar_t__) ; 
 int /*<<< orphan*/  netdev_printk (char*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  other_shmem_base_addr ; 
 int /*<<< orphan*/  pr_cont (char*,char*) ; 
 int /*<<< orphan*/  printk (char*,char const*,...) ; 

void bnx2x_fw_dump_lvl(struct bnx2x *bp, const char *lvl)
{
	u32 addr, val;
	u32 mark, offset;
	__be32 data[9];
	int word;
	u32 trace_shmem_base;
	if (BP_NOMCP(bp)) {
		BNX2X_ERR("NO MCP - can not dump\n");
		return;
	}
	printk("%s", lvl);
	netdev_printk("", bp->dev, "bc %d.%d.%d\n",
		(bp->common.bc_ver & 0xff0000) >> 16,
		(bp->common.bc_ver & 0xff00) >> 8,
		(bp->common.bc_ver & 0xff));

	val = REG_RD(bp, MCP_REG_MCPR_CPU_PROGRAM_COUNTER);
	if (val == REG_RD(bp, MCP_REG_MCPR_CPU_PROGRAM_COUNTER))
		BNX2X_ERR("%s" "MCP PC at 0x%x\n", lvl, val);

	if (BP_PATH(bp) == 0)
		trace_shmem_base = bp->common.shmem_base;
	else
		trace_shmem_base = SHMEM2_RD(bp, other_shmem_base_addr);
	addr = trace_shmem_base - 0x800;

	/* validate TRCB signature */
	mark = REG_RD(bp, addr);
	if (mark != MFW_TRACE_SIGNATURE) {
		BNX2X_ERR("Trace buffer signature is missing.");
		return ;
	}

	/* read cyclic buffer pointer */
	addr += 4;
	mark = REG_RD(bp, addr);
	mark = (CHIP_IS_E1x(bp) ? MCP_REG_MCPR_SCRATCH : MCP_A_REG_MCPR_SCRATCH)
			+ ((mark + 0x3) & ~0x3) - 0x08000000;
	printk("%s" "begin fw dump (mark 0x%x)\n", lvl, mark);

	printk("%s", lvl);

	/* dump buffer after the mark */
	for (offset = mark; offset <= trace_shmem_base; offset += 0x8*4) {
		for (word = 0; word < 8; word++)
			data[word] = htonl(REG_RD(bp, offset + 4*word));
		data[8] = 0x0;
		pr_cont("%s", (char *)data);
	}

	/* dump buffer before the mark */
	for (offset = addr + 4; offset <= mark; offset += 0x8*4) {
		for (word = 0; word < 8; word++)
			data[word] = htonl(REG_RD(bp, offset + 4*word));
		data[8] = 0x0;
		pr_cont("%s", (char *)data);
	}
	printk("%s" "end of fw dump\n", lvl);
}