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
typedef  int u32 ;
struct s3cmci_host {scalar_t__ base; int /*<<< orphan*/  complete_what; } ;
struct mmc_command {int flags; int arg; int opcode; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLETION_CMDSENT ; 
 int /*<<< orphan*/  COMPLETION_RSPFIN ; 
 int /*<<< orphan*/  COMPLETION_XFERFINISH_RSPFIN ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 scalar_t__ S3C2410_SDICMDARG ; 
 scalar_t__ S3C2410_SDICMDCON ; 
 int S3C2410_SDICMDCON_CMDSTART ; 
 int S3C2410_SDICMDCON_INDEX ; 
 int S3C2410_SDICMDCON_LONGRSP ; 
 int S3C2410_SDICMDCON_SENDERHOST ; 
 int S3C2410_SDICMDCON_WAITRSP ; 
 int S3C2410_SDIIMSK_CMDSENT ; 
 int S3C2410_SDIIMSK_CMDTIMEOUT ; 
 int S3C2410_SDIIMSK_CRCSTATUS ; 
 int S3C2410_SDIIMSK_RESPONSECRC ; 
 int S3C2410_SDIIMSK_RESPONSEND ; 
 int /*<<< orphan*/  enable_imask (struct s3cmci_host*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s3cmci_send_command(struct s3cmci_host *host,
					struct mmc_command *cmd)
{
	u32 ccon, imsk;

	imsk  = S3C2410_SDIIMSK_CRCSTATUS | S3C2410_SDIIMSK_CMDTIMEOUT |
		S3C2410_SDIIMSK_RESPONSEND | S3C2410_SDIIMSK_CMDSENT |
		S3C2410_SDIIMSK_RESPONSECRC;

	enable_imask(host, imsk);

	if (cmd->data)
		host->complete_what = COMPLETION_XFERFINISH_RSPFIN;
	else if (cmd->flags & MMC_RSP_PRESENT)
		host->complete_what = COMPLETION_RSPFIN;
	else
		host->complete_what = COMPLETION_CMDSENT;

	writel(cmd->arg, host->base + S3C2410_SDICMDARG);

	ccon  = cmd->opcode & S3C2410_SDICMDCON_INDEX;
	ccon |= S3C2410_SDICMDCON_SENDERHOST | S3C2410_SDICMDCON_CMDSTART;

	if (cmd->flags & MMC_RSP_PRESENT)
		ccon |= S3C2410_SDICMDCON_WAITRSP;

	if (cmd->flags & MMC_RSP_136)
		ccon |= S3C2410_SDICMDCON_LONGRSP;

	writel(ccon, host->base + S3C2410_SDICMDCON);
}