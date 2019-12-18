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
struct mddi_info {int /*<<< orphan*/  rev_addr; int /*<<< orphan*/  rev_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  MDDI_CMD_FORCE_NEW_REV_PTR ; 
 int /*<<< orphan*/  MDDI_INT_NO_CMD_PKTS_PEND ; 
 int /*<<< orphan*/  MDDI_REV_BUFFER_SIZE ; 
 int /*<<< orphan*/  REV_PTR ; 
 int /*<<< orphan*/  mddi_wait_interrupt (struct mddi_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mddi_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mddi_init_rev_encap(struct mddi_info *mddi)
{
	memset(mddi->rev_data, 0xee, MDDI_REV_BUFFER_SIZE);
	mddi_writel(mddi->rev_addr, REV_PTR);
	mddi_writel(MDDI_CMD_FORCE_NEW_REV_PTR, CMD);
	mddi_wait_interrupt(mddi, MDDI_INT_NO_CMD_PKTS_PEND);
}