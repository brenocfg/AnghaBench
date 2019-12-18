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
typedef  int /*<<< orphan*/  u32 ;
struct pm8001_hba_info {int iomb_size; } ;
struct outbound_queue_table {int consumer_idx; struct mpi_msg_hdr* producer_index; int /*<<< orphan*/  pi_virt; int /*<<< orphan*/  ci_offset; int /*<<< orphan*/  ci_pci_bar; scalar_t__ base_virt; } ;
struct mpi_msg_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_IO_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int PM8001_MPI_QUEUE ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_cw32 (struct pm8001_hba_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm8001_printk (char*,int,struct mpi_msg_hdr*,...) ; 
 int /*<<< orphan*/  pm8001_read_32 (int /*<<< orphan*/ ) ; 

u32 pm8001_mpi_msg_free_set(struct pm8001_hba_info *pm8001_ha, void *pMsg,
			    struct outbound_queue_table *circularQ, u8 bc)
{
	u32 producer_index;
	struct mpi_msg_hdr *msgHeader;
	struct mpi_msg_hdr *pOutBoundMsgHeader;

	msgHeader = (struct mpi_msg_hdr *)(pMsg - sizeof(struct mpi_msg_hdr));
	pOutBoundMsgHeader = (struct mpi_msg_hdr *)(circularQ->base_virt +
				circularQ->consumer_idx * pm8001_ha->iomb_size);
	if (pOutBoundMsgHeader != msgHeader) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("consumer_idx = %d msgHeader = %p\n",
			circularQ->consumer_idx, msgHeader));

		/* Update the producer index from SPC */
		producer_index = pm8001_read_32(circularQ->pi_virt);
		circularQ->producer_index = cpu_to_le32(producer_index);
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("consumer_idx = %d producer_index = %d"
			"msgHeader = %p\n", circularQ->consumer_idx,
			circularQ->producer_index, msgHeader));
		return 0;
	}
	/* free the circular queue buffer elements associated with the message*/
	circularQ->consumer_idx = (circularQ->consumer_idx + bc)
				% PM8001_MPI_QUEUE;
	/* update the CI of outbound queue */
	pm8001_cw32(pm8001_ha, circularQ->ci_pci_bar, circularQ->ci_offset,
		circularQ->consumer_idx);
	/* Update the producer index from SPC*/
	producer_index = pm8001_read_32(circularQ->pi_virt);
	circularQ->producer_index = cpu_to_le32(producer_index);
	PM8001_IO_DBG(pm8001_ha,
		pm8001_printk(" CI=%d PI=%d\n", circularQ->consumer_idx,
		circularQ->producer_index));
	return 0;
}