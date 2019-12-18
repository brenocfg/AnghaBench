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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct mpi_msg_hdr {int dummy; } ;
struct inbound_queue_table {int producer_idx; scalar_t__ base_virt; int /*<<< orphan*/  consumer_index; int /*<<< orphan*/  ci_virt; } ;

/* Variables and functions */
 int IOMB_SIZE_SPCV ; 
 int PM8001_MPI_QUEUE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int pm8001_read_32 (int /*<<< orphan*/ ) ; 

int pm8001_mpi_msg_free_get(struct inbound_queue_table *circularQ,
			    u16 messageSize, void **messagePtr)
{
	u32 offset, consumer_index;
	struct mpi_msg_hdr *msgHeader;
	u8 bcCount = 1; /* only support single buffer */

	/* Checks is the requested message size can be allocated in this queue*/
	if (messageSize > IOMB_SIZE_SPCV) {
		*messagePtr = NULL;
		return -1;
	}

	/* Stores the new consumer index */
	consumer_index = pm8001_read_32(circularQ->ci_virt);
	circularQ->consumer_index = cpu_to_le32(consumer_index);
	if (((circularQ->producer_idx + bcCount) % PM8001_MPI_QUEUE) ==
		le32_to_cpu(circularQ->consumer_index)) {
		*messagePtr = NULL;
		return -1;
	}
	/* get memory IOMB buffer address */
	offset = circularQ->producer_idx * messageSize;
	/* increment to next bcCount element */
	circularQ->producer_idx = (circularQ->producer_idx + bcCount)
				% PM8001_MPI_QUEUE;
	/* Adds that distance to the base of the region virtual address plus
	the message header size*/
	msgHeader = (struct mpi_msg_hdr *)(circularQ->base_virt	+ offset);
	*messagePtr = ((void *)msgHeader) + sizeof(struct mpi_msg_hdr);
	return 0;
}