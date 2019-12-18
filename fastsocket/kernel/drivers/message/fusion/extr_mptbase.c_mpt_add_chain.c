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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  Address; int /*<<< orphan*/  NextChainOffset; int /*<<< orphan*/  Flags; int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ SGEChain32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_SGE_FLAGS_CHAIN_ELEMENT ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mpt_add_chain(void *pAddr, u8 next, u16 length, dma_addr_t dma_addr)
{
		SGEChain32_t *pChain = (SGEChain32_t *) pAddr;
		pChain->Length = cpu_to_le16(length);
		pChain->Flags = MPI_SGE_FLAGS_CHAIN_ELEMENT;
		pChain->NextChainOffset = next;
		pChain->Address = cpu_to_le32(dma_addr);
}