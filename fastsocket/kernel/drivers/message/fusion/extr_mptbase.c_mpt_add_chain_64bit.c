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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int dma_addr_t ;
struct TYPE_3__ {void* High; void* Low; } ;
struct TYPE_4__ {int Flags; TYPE_1__ Address; int /*<<< orphan*/  NextChainOffset; int /*<<< orphan*/  Length; } ;
typedef  TYPE_2__ SGEChain64_t ;

/* Variables and functions */
 int MPI_SGE_FLAGS_64_BIT_ADDRESSING ; 
 int MPI_SGE_FLAGS_CHAIN_ELEMENT ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ upper_32_bits (int) ; 

__attribute__((used)) static void
mpt_add_chain_64bit(void *pAddr, u8 next, u16 length, dma_addr_t dma_addr)
{
		SGEChain64_t *pChain = (SGEChain64_t *) pAddr;
		u32 tmp = dma_addr & 0xFFFFFFFF;

		pChain->Length = cpu_to_le16(length);
		pChain->Flags = (MPI_SGE_FLAGS_CHAIN_ELEMENT |
				 MPI_SGE_FLAGS_64_BIT_ADDRESSING);

		pChain->NextChainOffset = next;

		pChain->Address.Low = cpu_to_le32(tmp);
		tmp = (u32)(upper_32_bits(dma_addr));
		pChain->Address.High = cpu_to_le32(tmp);
}