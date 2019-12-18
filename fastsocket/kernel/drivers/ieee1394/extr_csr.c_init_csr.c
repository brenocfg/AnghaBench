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

/* Variables and functions */
 int /*<<< orphan*/  CSR1212_KV_ID_NODE_CAPABILITIES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HPSB_ERR (char*) ; 
 int /*<<< orphan*/  csr1212_new_immediate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csr_highlevel ; 
 int /*<<< orphan*/  hpsb_register_highlevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_cap ; 

int init_csr(void)
{
	node_cap = csr1212_new_immediate(CSR1212_KV_ID_NODE_CAPABILITIES, 0x0083c0);
	if (!node_cap) {
		HPSB_ERR("Failed to allocate memory for Node Capabilties ConfigROM entry!");
		return -ENOMEM;
	}

	hpsb_register_highlevel(&csr_highlevel);

	return 0;
}