#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct node_entry {int generation; scalar_t__ nodeid; TYPE_2__* host; } ;
typedef  int quadlet_t ;
typedef  int /*<<< orphan*/  bc_remote ;
typedef  int /*<<< orphan*/  bc_local ;
struct TYPE_3__ {int broadcast_channel; } ;
struct TYPE_4__ {scalar_t__ node_id; TYPE_1__ csr; int /*<<< orphan*/  is_irm; } ;

/* Variables and functions */
 int CSR_BROADCAST_CHANNEL ; 
 int CSR_REGISTER_BASE ; 
 int cpu_to_be32 (int) ; 
 int /*<<< orphan*/  hpsb_node_write (struct node_entry*,int const,int*,int) ; 
 int hpsb_read (TYPE_2__*,scalar_t__,int,int const,int*,int) ; 

__attribute__((used)) static void nodemgr_irm_write_bc(struct node_entry *ne, int generation)
{
	const u64 bc_addr = (CSR_REGISTER_BASE | CSR_BROADCAST_CHANNEL);
	quadlet_t bc_remote, bc_local;
	int error;

	if (!ne->host->is_irm || ne->generation != generation ||
	    ne->nodeid == ne->host->node_id)
		return;

	bc_local = cpu_to_be32(ne->host->csr.broadcast_channel);

	/* Check if the register is implemented and 1394a compliant. */
	error = hpsb_read(ne->host, ne->nodeid, generation, bc_addr, &bc_remote,
			  sizeof(bc_remote));
	if (!error && bc_remote & cpu_to_be32(0x80000000) &&
	    bc_remote != bc_local)
		hpsb_node_write(ne, bc_addr, &bc_local, sizeof(bc_local));
}