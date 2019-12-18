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
struct hpsb_host {int /*<<< orphan*/  id; scalar_t__ update_config_rom; } ;
struct hpsb_highlevel {int /*<<< orphan*/  name; int /*<<< orphan*/  (* add_host ) (struct hpsb_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HPSB_ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hpsb_update_config_rom_image (struct hpsb_host*) ; 
 int /*<<< orphan*/  stub1 (struct hpsb_host*) ; 

__attribute__((used)) static int highlevel_for_each_host_reg(struct hpsb_host *host, void *__data)
{
	struct hpsb_highlevel *hl = __data;

	hl->add_host(host);

	if (host->update_config_rom && hpsb_update_config_rom_image(host) < 0)
		HPSB_ERR("Failed to generate Configuration ROM image for host "
			 "%s-%d", hl->name, host->id);
	return 0;
}