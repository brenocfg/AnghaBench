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
 int /*<<< orphan*/  au1xmmc_finish_request (struct au1xmmc_host*) ; 

__attribute__((used)) static void au1xmmc_tasklet_finish(unsigned long param)
{
	struct au1xmmc_host *host = (struct au1xmmc_host *) param;
	au1xmmc_finish_request(host);
}