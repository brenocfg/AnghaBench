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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hpsb_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR1212_UNITS_SPACE_BASE ; 
 int /*<<< orphan*/  CSR1212_UNITS_SPACE_END ; 
 int /*<<< orphan*/  config_rom_ops ; 
 int /*<<< orphan*/  csr_highlevel ; 
 int /*<<< orphan*/  hpsb_allocate_and_register_addrspace (int /*<<< orphan*/ *,struct hpsb_host*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 allocate_addr_range(u64 size, u32 alignment, void *__host)
{
 	struct hpsb_host *host = (struct hpsb_host*)__host;

	return hpsb_allocate_and_register_addrspace(&csr_highlevel,
						    host,
						    &config_rom_ops,
						    size, alignment,
						    CSR1212_UNITS_SPACE_BASE,
						    CSR1212_UNITS_SPACE_END);
}