#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  rom; } ;
struct hpsb_host {TYPE_1__ csr; } ;
typedef  int /*<<< orphan*/  quadlet_t ;

/* Variables and functions */
 scalar_t__ CSR1212_REGISTER_SPACE_BASE ; 
 scalar_t__ CSR1212_SUCCESS ; 
 int RCODE_ADDRESS_ERROR ; 
 int RCODE_COMPLETE ; 
 scalar_t__ csr1212_read (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int read_config_rom(struct hpsb_host *host, int nodeid, quadlet_t *buffer,
			   u64 addr, size_t length, u16 fl)
{
	u32 offset = addr - CSR1212_REGISTER_SPACE_BASE;

	if (csr1212_read(host->csr.rom, offset, buffer, length) == CSR1212_SUCCESS)
		return RCODE_COMPLETE;
	else
		return RCODE_ADDRESS_ERROR;
}