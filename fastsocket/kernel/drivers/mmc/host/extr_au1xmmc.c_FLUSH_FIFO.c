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
struct au1xmmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_CONFIG2 (struct au1xmmc_host*) ; 
 int SD_CONFIG2_DF ; 
 int SD_CONFIG2_FF ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_sync_delay (int) ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void FLUSH_FIFO(struct au1xmmc_host *host)
{
	u32 val = au_readl(HOST_CONFIG2(host));

	au_writel(val | SD_CONFIG2_FF, HOST_CONFIG2(host));
	au_sync_delay(1);

	/* SEND_STOP will turn off clock control - this re-enables it */
	val &= ~SD_CONFIG2_DF;

	au_writel(val, HOST_CONFIG2(host));
	au_sync();
}