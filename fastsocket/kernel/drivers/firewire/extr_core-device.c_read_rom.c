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
typedef  int /*<<< orphan*/  u32 ;
struct fw_device {int /*<<< orphan*/  max_speed; int /*<<< orphan*/  node_id; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int CSR_CONFIG_ROM ; 
 int CSR_REGISTER_BASE ; 
 int /*<<< orphan*/  TCODE_READ_QUADLET_REQUEST ; 
 int /*<<< orphan*/  be32_to_cpus (int /*<<< orphan*/ *) ; 
 int fw_run_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static int read_rom(struct fw_device *device,
		    int generation, int index, u32 *data)
{
	int rcode;

	/* device->node_id, accessed below, must not be older than generation */
	smp_rmb();

	rcode = fw_run_transaction(device->card, TCODE_READ_QUADLET_REQUEST,
			device->node_id, generation, device->max_speed,
			(CSR_REGISTER_BASE | CSR_CONFIG_ROM) + index * 4,
			data, 4);
	be32_to_cpus(data);

	return rcode;
}