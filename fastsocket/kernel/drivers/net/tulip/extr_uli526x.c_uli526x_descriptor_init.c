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
struct uli526x_board_info {int first_tx_desc_dma; int first_rx_desc_dma; unsigned char* buf_pool_start; int buf_pool_dma_start; struct rx_desc* first_rx_desc; struct tx_desc* first_tx_desc; struct rx_desc* rx_ready_ptr; struct rx_desc* rx_insert_ptr; struct tx_desc* tx_remove_ptr; struct tx_desc* tx_insert_ptr; } ;
struct tx_desc {unsigned char* tx_buf_ptr; struct tx_desc* next_tx_desc; void* tdes3; void* tdes2; void* tdes1; void* tdes0; } ;
struct rx_desc {struct rx_desc* next_rx_desc; void* rdes3; void* rdes1; void* rdes0; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ DCR3 ; 
 scalar_t__ DCR4 ; 
 int RX_DESC_CNT ; 
 int TX_BUF_ALLOC ; 
 int TX_DESC_CNT ; 
 int /*<<< orphan*/  ULI526X_DBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allocate_rx_buffer (struct uli526x_board_info*) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static void uli526x_descriptor_init(struct uli526x_board_info *db, unsigned long ioaddr)
{
	struct tx_desc *tmp_tx;
	struct rx_desc *tmp_rx;
	unsigned char *tmp_buf;
	dma_addr_t tmp_tx_dma, tmp_rx_dma;
	dma_addr_t tmp_buf_dma;
	int i;

	ULI526X_DBUG(0, "uli526x_descriptor_init()", 0);

	/* tx descriptor start pointer */
	db->tx_insert_ptr = db->first_tx_desc;
	db->tx_remove_ptr = db->first_tx_desc;
	outl(db->first_tx_desc_dma, ioaddr + DCR4);     /* TX DESC address */

	/* rx descriptor start pointer */
	db->first_rx_desc = (void *)db->first_tx_desc + sizeof(struct tx_desc) * TX_DESC_CNT;
	db->first_rx_desc_dma =  db->first_tx_desc_dma + sizeof(struct tx_desc) * TX_DESC_CNT;
	db->rx_insert_ptr = db->first_rx_desc;
	db->rx_ready_ptr = db->first_rx_desc;
	outl(db->first_rx_desc_dma, ioaddr + DCR3);	/* RX DESC address */

	/* Init Transmit chain */
	tmp_buf = db->buf_pool_start;
	tmp_buf_dma = db->buf_pool_dma_start;
	tmp_tx_dma = db->first_tx_desc_dma;
	for (tmp_tx = db->first_tx_desc, i = 0; i < TX_DESC_CNT; i++, tmp_tx++) {
		tmp_tx->tx_buf_ptr = tmp_buf;
		tmp_tx->tdes0 = cpu_to_le32(0);
		tmp_tx->tdes1 = cpu_to_le32(0x81000000);	/* IC, chain */
		tmp_tx->tdes2 = cpu_to_le32(tmp_buf_dma);
		tmp_tx_dma += sizeof(struct tx_desc);
		tmp_tx->tdes3 = cpu_to_le32(tmp_tx_dma);
		tmp_tx->next_tx_desc = tmp_tx + 1;
		tmp_buf = tmp_buf + TX_BUF_ALLOC;
		tmp_buf_dma = tmp_buf_dma + TX_BUF_ALLOC;
	}
	(--tmp_tx)->tdes3 = cpu_to_le32(db->first_tx_desc_dma);
	tmp_tx->next_tx_desc = db->first_tx_desc;

	 /* Init Receive descriptor chain */
	tmp_rx_dma=db->first_rx_desc_dma;
	for (tmp_rx = db->first_rx_desc, i = 0; i < RX_DESC_CNT; i++, tmp_rx++) {
		tmp_rx->rdes0 = cpu_to_le32(0);
		tmp_rx->rdes1 = cpu_to_le32(0x01000600);
		tmp_rx_dma += sizeof(struct rx_desc);
		tmp_rx->rdes3 = cpu_to_le32(tmp_rx_dma);
		tmp_rx->next_rx_desc = tmp_rx + 1;
	}
	(--tmp_rx)->rdes3 = cpu_to_le32(db->first_rx_desc_dma);
	tmp_rx->next_rx_desc = db->first_rx_desc;

	/* pre-allocate Rx buffer */
	allocate_rx_buffer(db);
}