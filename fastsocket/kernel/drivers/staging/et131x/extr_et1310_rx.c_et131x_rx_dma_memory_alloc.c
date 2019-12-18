#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int PsrNumEntries; int Fbr0NumEntries; int Fbr1NumEntries; } ;
struct et131x_adapter {int RegistryJumboPacket; int /*<<< orphan*/  Flags; TYPE_3__* netdev; TYPE_5__* pdev; TYPE_2__ RxRing; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int Fbr0BufferSize; int Fbr0NumEntries; int Fbr1BufferSize; int Fbr1NumEntries; int pFbr1RingPa; int Fbr1Realpa; int Fbr1offset; int pFbr0RingPa; int Fbr0Realpa; int Fbr0offset; int* Fbr1MemPa; int* Fbr0MemPa; int pPSRingPa; int pPSRingRealPa; int pPSRingOffset; int pRxStatusPa; int RxStatusRealPA; int RxStatusOffset; int /*<<< orphan*/  RecvPendingList; int /*<<< orphan*/  RecvList; int /*<<< orphan*/  RecvLookaside; int /*<<< orphan*/  NumRfd; void* pRxStatusVa; void* pPSRingVa; TYPE_1__** Fbr; void** Fbr0MemVa; void** Fbr1MemVa; void* pFbr0RingVa; void* pFbr1RingVa; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int* PAHigh; int* PALow; int /*<<< orphan*/ ** Va; int /*<<< orphan*/ ** Buffer2; int /*<<< orphan*/ ** Buffer1; } ;
typedef  int /*<<< orphan*/  RX_STATUS_BLOCK_t ;
typedef  TYPE_4__ RX_RING_t ;
typedef  int /*<<< orphan*/  PKT_STAT_DESC_t ;
typedef  int /*<<< orphan*/  MP_RFD ;
typedef  int /*<<< orphan*/  FBR_DESC_t ;
typedef  int /*<<< orphan*/  FBRLOOKUPTABLE ;

/* Variables and functions */
 int ENOMEM ; 
 int FBR_CHUNKS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIC_DEFAULT_NUM_RFD ; 
 int SLAB_CACHE_DMA ; 
 int SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  et131x_align_allocated_memory (struct et131x_adapter*,int*,int*,int) ; 
 int /*<<< orphan*/  fMP_ADAPTER_RECV_LOOKASIDE ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* pci_alloc_consistent (TYPE_5__*,int,int*) ; 

int et131x_rx_dma_memory_alloc(struct et131x_adapter *adapter)
{
	uint32_t OuterLoop, InnerLoop;
	uint32_t bufsize;
	uint32_t pktStatRingSize, FBRChunkSize;
	RX_RING_t *rx_ring;

	/* Setup some convenience pointers */
	rx_ring = (RX_RING_t *) &adapter->RxRing;

	/* Alloc memory for the lookup table */
#ifdef USE_FBR0
	rx_ring->Fbr[0] = kmalloc(sizeof(FBRLOOKUPTABLE), GFP_KERNEL);
#endif

	rx_ring->Fbr[1] = kmalloc(sizeof(FBRLOOKUPTABLE), GFP_KERNEL);

	/* The first thing we will do is configure the sizes of the buffer
	 * rings. These will change based on jumbo packet support.  Larger
	 * jumbo packets increases the size of each entry in FBR0, and the
	 * number of entries in FBR0, while at the same time decreasing the
	 * number of entries in FBR1.
	 *
	 * FBR1 holds "large" frames, FBR0 holds "small" frames.  If FBR1
	 * entries are huge in order to accomodate a "jumbo" frame, then it
	 * will have less entries.  Conversely, FBR1 will now be relied upon
	 * to carry more "normal" frames, thus it's entry size also increases
	 * and the number of entries goes up too (since it now carries
	 * "small" + "regular" packets.
	 *
	 * In this scheme, we try to maintain 512 entries between the two
	 * rings. Also, FBR1 remains a constant size - when it's size doubles
	 * the number of entries halves.  FBR0 increases in size, however.
	 */

	if (adapter->RegistryJumboPacket < 2048) {
#ifdef USE_FBR0
		rx_ring->Fbr0BufferSize = 256;
		rx_ring->Fbr0NumEntries = 512;
#endif
		rx_ring->Fbr1BufferSize = 2048;
		rx_ring->Fbr1NumEntries = 512;
	} else if (adapter->RegistryJumboPacket < 4096) {
#ifdef USE_FBR0
		rx_ring->Fbr0BufferSize = 512;
		rx_ring->Fbr0NumEntries = 1024;
#endif
		rx_ring->Fbr1BufferSize = 4096;
		rx_ring->Fbr1NumEntries = 512;
	} else {
#ifdef USE_FBR0
		rx_ring->Fbr0BufferSize = 1024;
		rx_ring->Fbr0NumEntries = 768;
#endif
		rx_ring->Fbr1BufferSize = 16384;
		rx_ring->Fbr1NumEntries = 128;
	}

#ifdef USE_FBR0
	adapter->RxRing.PsrNumEntries = adapter->RxRing.Fbr0NumEntries +
	    adapter->RxRing.Fbr1NumEntries;
#else
	adapter->RxRing.PsrNumEntries = adapter->RxRing.Fbr1NumEntries;
#endif

	/* Allocate an area of memory for Free Buffer Ring 1 */
	bufsize = (sizeof(FBR_DESC_t) * rx_ring->Fbr1NumEntries) + 0xfff;
	rx_ring->pFbr1RingVa = pci_alloc_consistent(adapter->pdev,
						    bufsize,
						    &rx_ring->pFbr1RingPa);
	if (!rx_ring->pFbr1RingVa) {
		dev_err(&adapter->pdev->dev,
			  "Cannot alloc memory for Free Buffer Ring 1\n");
		return -ENOMEM;
	}

	/* Save physical address
	 *
	 * NOTE: pci_alloc_consistent(), used above to alloc DMA regions,
	 * ALWAYS returns SAC (32-bit) addresses. If DAC (64-bit) addresses
	 * are ever returned, make sure the high part is retrieved here
	 * before storing the adjusted address.
	 */
	rx_ring->Fbr1Realpa = rx_ring->pFbr1RingPa;

	/* Align Free Buffer Ring 1 on a 4K boundary */
	et131x_align_allocated_memory(adapter,
				      &rx_ring->Fbr1Realpa,
				      &rx_ring->Fbr1offset, 0x0FFF);

	rx_ring->pFbr1RingVa = (void *)((uint8_t *) rx_ring->pFbr1RingVa +
					rx_ring->Fbr1offset);

#ifdef USE_FBR0
	/* Allocate an area of memory for Free Buffer Ring 0 */
	bufsize = (sizeof(FBR_DESC_t) * rx_ring->Fbr0NumEntries) + 0xfff;
	rx_ring->pFbr0RingVa = pci_alloc_consistent(adapter->pdev,
						    bufsize,
						    &rx_ring->pFbr0RingPa);
	if (!rx_ring->pFbr0RingVa) {
		dev_err(&adapter->pdev->dev,
			  "Cannot alloc memory for Free Buffer Ring 0\n");
		return -ENOMEM;
	}

	/* Save physical address
	 *
	 * NOTE: pci_alloc_consistent(), used above to alloc DMA regions,
	 * ALWAYS returns SAC (32-bit) addresses. If DAC (64-bit) addresses
	 * are ever returned, make sure the high part is retrieved here before
	 * storing the adjusted address.
	 */
	rx_ring->Fbr0Realpa = rx_ring->pFbr0RingPa;

	/* Align Free Buffer Ring 0 on a 4K boundary */
	et131x_align_allocated_memory(adapter,
				      &rx_ring->Fbr0Realpa,
				      &rx_ring->Fbr0offset, 0x0FFF);

	rx_ring->pFbr0RingVa = (void *)((uint8_t *) rx_ring->pFbr0RingVa +
					rx_ring->Fbr0offset);
#endif

	for (OuterLoop = 0; OuterLoop < (rx_ring->Fbr1NumEntries / FBR_CHUNKS);
	     OuterLoop++) {
		uint64_t Fbr1Offset;
		uint64_t Fbr1TempPa;
		uint32_t Fbr1Align;

		/* This code allocates an area of memory big enough for N
		 * free buffers + (buffer_size - 1) so that the buffers can
		 * be aligned on 4k boundaries.  If each buffer were aligned
		 * to a buffer_size boundary, the effect would be to double
		 * the size of FBR0.  By allocating N buffers at once, we
		 * reduce this overhead.
		 */
		if (rx_ring->Fbr1BufferSize > 4096)
			Fbr1Align = 4096;
		else
			Fbr1Align = rx_ring->Fbr1BufferSize;

		FBRChunkSize =
		    (FBR_CHUNKS * rx_ring->Fbr1BufferSize) + Fbr1Align - 1;
		rx_ring->Fbr1MemVa[OuterLoop] =
		    pci_alloc_consistent(adapter->pdev, FBRChunkSize,
					 &rx_ring->Fbr1MemPa[OuterLoop]);

		if (!rx_ring->Fbr1MemVa[OuterLoop]) {
		dev_err(&adapter->pdev->dev,
				"Could not alloc memory\n");
			return -ENOMEM;
		}

		/* See NOTE in "Save Physical Address" comment above */
		Fbr1TempPa = rx_ring->Fbr1MemPa[OuterLoop];

		et131x_align_allocated_memory(adapter,
					      &Fbr1TempPa,
					      &Fbr1Offset, (Fbr1Align - 1));

		for (InnerLoop = 0; InnerLoop < FBR_CHUNKS; InnerLoop++) {
			uint32_t index = (OuterLoop * FBR_CHUNKS) + InnerLoop;

			/* Save the Virtual address of this index for quick
			 * access later
			 */
			rx_ring->Fbr[1]->Va[index] =
			    (uint8_t *) rx_ring->Fbr1MemVa[OuterLoop] +
			    (InnerLoop * rx_ring->Fbr1BufferSize) + Fbr1Offset;

			/* now store the physical address in the descriptor
			 * so the device can access it
			 */
			rx_ring->Fbr[1]->PAHigh[index] =
			    (uint32_t) (Fbr1TempPa >> 32);
			rx_ring->Fbr[1]->PALow[index] = (uint32_t) Fbr1TempPa;

			Fbr1TempPa += rx_ring->Fbr1BufferSize;

			rx_ring->Fbr[1]->Buffer1[index] =
			    rx_ring->Fbr[1]->Va[index];
			rx_ring->Fbr[1]->Buffer2[index] =
			    rx_ring->Fbr[1]->Va[index] - 4;
		}
	}

#ifdef USE_FBR0
	/* Same for FBR0 (if in use) */
	for (OuterLoop = 0; OuterLoop < (rx_ring->Fbr0NumEntries / FBR_CHUNKS);
	     OuterLoop++) {
		uint64_t Fbr0Offset;
		uint64_t Fbr0TempPa;

		FBRChunkSize = ((FBR_CHUNKS + 1) * rx_ring->Fbr0BufferSize) - 1;
		rx_ring->Fbr0MemVa[OuterLoop] =
		    pci_alloc_consistent(adapter->pdev, FBRChunkSize,
					 &rx_ring->Fbr0MemPa[OuterLoop]);

		if (!rx_ring->Fbr0MemVa[OuterLoop]) {
			dev_err(&adapter->pdev->dev,
				"Could not alloc memory\n");
			return -ENOMEM;
		}

		/* See NOTE in "Save Physical Address" comment above */
		Fbr0TempPa = rx_ring->Fbr0MemPa[OuterLoop];

		et131x_align_allocated_memory(adapter,
					      &Fbr0TempPa,
					      &Fbr0Offset,
					      rx_ring->Fbr0BufferSize - 1);

		for (InnerLoop = 0; InnerLoop < FBR_CHUNKS; InnerLoop++) {
			uint32_t index = (OuterLoop * FBR_CHUNKS) + InnerLoop;

			rx_ring->Fbr[0]->Va[index] =
			    (uint8_t *) rx_ring->Fbr0MemVa[OuterLoop] +
			    (InnerLoop * rx_ring->Fbr0BufferSize) + Fbr0Offset;

			rx_ring->Fbr[0]->PAHigh[index] =
			    (uint32_t) (Fbr0TempPa >> 32);
			rx_ring->Fbr[0]->PALow[index] = (uint32_t) Fbr0TempPa;

			Fbr0TempPa += rx_ring->Fbr0BufferSize;

			rx_ring->Fbr[0]->Buffer1[index] =
			    rx_ring->Fbr[0]->Va[index];
			rx_ring->Fbr[0]->Buffer2[index] =
			    rx_ring->Fbr[0]->Va[index] - 4;
		}
	}
#endif

	/* Allocate an area of memory for FIFO of Packet Status ring entries */
	pktStatRingSize =
	    sizeof(PKT_STAT_DESC_t) * adapter->RxRing.PsrNumEntries;

	rx_ring->pPSRingVa = pci_alloc_consistent(adapter->pdev,
						  pktStatRingSize + 0x0fff,
						  &rx_ring->pPSRingPa);

	if (!rx_ring->pPSRingVa) {
		dev_err(&adapter->pdev->dev,
			  "Cannot alloc memory for Packet Status Ring\n");
		return -ENOMEM;
	}

	/* Save physical address
	 *
	 * NOTE : pci_alloc_consistent(), used above to alloc DMA regions,
	 * ALWAYS returns SAC (32-bit) addresses. If DAC (64-bit) addresses
	 * are ever returned, make sure the high part is retrieved here before
	 * storing the adjusted address.
	 */
	rx_ring->pPSRingRealPa = rx_ring->pPSRingPa;

	/* Align Packet Status Ring on a 4K boundary */
	et131x_align_allocated_memory(adapter,
				      &rx_ring->pPSRingRealPa,
				      &rx_ring->pPSRingOffset, 0x0FFF);

	rx_ring->pPSRingVa = (void *)((uint8_t *) rx_ring->pPSRingVa +
				      rx_ring->pPSRingOffset);

	/* Allocate an area of memory for writeback of status information */
	rx_ring->pRxStatusVa = pci_alloc_consistent(adapter->pdev,
						    sizeof(RX_STATUS_BLOCK_t) +
						    0x7, &rx_ring->pRxStatusPa);
	if (!rx_ring->pRxStatusVa) {
		dev_err(&adapter->pdev->dev,
			  "Cannot alloc memory for Status Block\n");
		return -ENOMEM;
	}

	/* Save physical address */
	rx_ring->RxStatusRealPA = rx_ring->pRxStatusPa;

	/* Align write back on an 8 byte boundary */
	et131x_align_allocated_memory(adapter,
				      &rx_ring->RxStatusRealPA,
				      &rx_ring->RxStatusOffset, 0x07);

	rx_ring->pRxStatusVa = (void *)((uint8_t *) rx_ring->pRxStatusVa +
					rx_ring->RxStatusOffset);
	rx_ring->NumRfd = NIC_DEFAULT_NUM_RFD;

	/* Recv
	 * pci_pool_create initializes a lookaside list. After successful
	 * creation, nonpaged fixed-size blocks can be allocated from and
	 * freed to the lookaside list.
	 * RFDs will be allocated from this pool.
	 */
	rx_ring->RecvLookaside = kmem_cache_create(adapter->netdev->name,
						   sizeof(MP_RFD),
						   0,
						   SLAB_CACHE_DMA |
						   SLAB_HWCACHE_ALIGN,
						   NULL);

	adapter->Flags |= fMP_ADAPTER_RECV_LOOKASIDE;

	/* The RFDs are going to be put on lists later on, so initialize the
	 * lists now.
	 */
	INIT_LIST_HEAD(&rx_ring->RecvList);
	INIT_LIST_HEAD(&rx_ring->RecvPendingList);
	return 0;
}