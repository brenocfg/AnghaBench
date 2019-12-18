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
typedef  int /*<<< orphan*/  u16 ;
struct rio_mport {int /*<<< orphan*/  sys_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIO_DID_CSR ; 
 int /*<<< orphan*/  RIO_SET_DID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rio_local_write_config_32 (struct rio_mport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rio_local_set_device_id(struct rio_mport *port, u16 did)
{
	rio_local_write_config_32(port, RIO_DID_CSR, RIO_SET_DID(port->sys_size,
				did));
}