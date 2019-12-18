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
struct au1xmmc_host {int dummy; } ;

/* Variables and functions */
 int AU1XMMC_INTERRUPTS ; 
 int /*<<< orphan*/  HOST_BLKSIZE (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_CONFIG (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_CONFIG2 (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_ENABLE (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_STATUS (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_TIMEOUT (struct au1xmmc_host*) ; 
 int SD_CONFIG2_EN ; 
 int SD_CONFIG2_FF ; 
 int SD_ENABLE_CE ; 
 int SD_ENABLE_R ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_sync_delay (int) ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void au1xmmc_reset_controller(struct au1xmmc_host *host)
{
	/* Apply the clock */
	au_writel(SD_ENABLE_CE, HOST_ENABLE(host));
        au_sync_delay(1);

	au_writel(SD_ENABLE_R | SD_ENABLE_CE, HOST_ENABLE(host));
	au_sync_delay(5);

	au_writel(~0, HOST_STATUS(host));
	au_sync();

	au_writel(0, HOST_BLKSIZE(host));
	au_writel(0x001fffff, HOST_TIMEOUT(host));
	au_sync();

	au_writel(SD_CONFIG2_EN, HOST_CONFIG2(host));
        au_sync();

	au_writel(SD_CONFIG2_EN | SD_CONFIG2_FF, HOST_CONFIG2(host));
	au_sync_delay(1);

	au_writel(SD_CONFIG2_EN, HOST_CONFIG2(host));
	au_sync();

	/* Configure interrupts */
	au_writel(AU1XMMC_INTERRUPTS, HOST_CONFIG(host));
	au_sync();
}