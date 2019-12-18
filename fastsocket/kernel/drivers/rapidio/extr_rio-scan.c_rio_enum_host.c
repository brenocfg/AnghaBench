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
struct rio_mport {int host_deviceid; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIO_HOST_DID_LOCK_CSR ; 
 int next_destid ; 
 int /*<<< orphan*/  rio_local_read_config_32 (struct rio_mport*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rio_local_set_device_id (struct rio_mport*,int) ; 
 int /*<<< orphan*/  rio_local_write_config_32 (struct rio_mport*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rio_enum_host(struct rio_mport *port)
{
	u32 result;

	/* Set master port host device id lock */
	rio_local_write_config_32(port, RIO_HOST_DID_LOCK_CSR,
				  port->host_deviceid);

	rio_local_read_config_32(port, RIO_HOST_DID_LOCK_CSR, &result);
	if ((result & 0xffff) != port->host_deviceid)
		return -1;

	/* Set master port destid and init destid ctr */
	rio_local_set_device_id(port, port->host_deviceid);

	if (next_destid == port->host_deviceid)
		next_destid++;

	return 0;
}