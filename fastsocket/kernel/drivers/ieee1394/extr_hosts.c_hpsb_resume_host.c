#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* rom; } ;
struct hpsb_host {TYPE_3__* driver; TYPE_2__ csr; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* devctl ) (struct hpsb_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_hw_config_rom ) (struct hpsb_host*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  bus_info_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESET_BUS ; 
 int /*<<< orphan*/  SHORT_RESET ; 
 int /*<<< orphan*/  stub1 (struct hpsb_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct hpsb_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hpsb_resume_host(struct hpsb_host *host)
{
	if (host->driver->set_hw_config_rom)
		host->driver->set_hw_config_rom(host,
						host->csr.rom->bus_info_data);
	host->driver->devctl(host, RESET_BUS, SHORT_RESET);
}