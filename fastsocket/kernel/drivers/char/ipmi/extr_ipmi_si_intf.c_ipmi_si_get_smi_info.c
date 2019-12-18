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
struct smi_info {scalar_t__ token; int /*<<< orphan*/  dev; int /*<<< orphan*/  addr_info; int /*<<< orphan*/  addr_source; } ;
struct ipmi_smi_info {int /*<<< orphan*/  addr_info; int /*<<< orphan*/  dev; int /*<<< orphan*/  addr_src; } ;

/* Variables and functions */
 int ENOSYS ; 
 scalar_t__ SI_INTF_TOKEN ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ ) ; 

int ipmi_si_get_smi_info(void *send_info, struct ipmi_smi_info *data)
{
	struct smi_info *smi = send_info;

	if (!smi || (smi->token != SI_INTF_TOKEN))
		return -ENOSYS;

	data->addr_src = smi->addr_source;
	data->dev = smi->dev;
	data->addr_info = smi->addr_info;
	get_device(smi->dev);

	return 0;
}