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
struct tifm_dev {scalar_t__ addr; } ;
struct mmc_command {int* resp; } ;

/* Variables and functions */
 scalar_t__ SOCK_MMCSD_RESPONSE ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void tifm_sd_fetch_resp(struct mmc_command *cmd, struct tifm_dev *sock)
{
	cmd->resp[0] = (readl(sock->addr + SOCK_MMCSD_RESPONSE + 0x1c) << 16)
		       | readl(sock->addr + SOCK_MMCSD_RESPONSE + 0x18);
	cmd->resp[1] = (readl(sock->addr + SOCK_MMCSD_RESPONSE + 0x14) << 16)
		       | readl(sock->addr + SOCK_MMCSD_RESPONSE + 0x10);
	cmd->resp[2] = (readl(sock->addr + SOCK_MMCSD_RESPONSE + 0x0c) << 16)
		       | readl(sock->addr + SOCK_MMCSD_RESPONSE + 0x08);
	cmd->resp[3] = (readl(sock->addr + SOCK_MMCSD_RESPONSE + 0x04) << 16)
		       | readl(sock->addr + SOCK_MMCSD_RESPONSE + 0x00);
}