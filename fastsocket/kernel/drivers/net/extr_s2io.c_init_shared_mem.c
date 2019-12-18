#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct tx_fifo_config {int fifo_len; } ;
struct TYPE_14__ {unsigned long long mem_allocated; } ;
struct stat_block {TYPE_6__ sw_stat; } ;
struct mac_info {void* stats_mem_phy; int stats_mem_sz; struct stat_block* stats_info; void* stats_mem; struct ring_info* rings; struct fifo_info* fifos; void* zerodma_virt_addr; } ;
struct config_param {int tx_fifo_num; int max_txds; int rx_ring_num; struct rx_ring_config* rx_cfg; struct tx_fifo_config* tx_cfg; } ;
struct s2io_nic {size_t rxd_mode; TYPE_7__* pdev; struct mac_info mac_control; struct config_param config; struct net_device* dev; } ;
struct rxd_info {int dummy; } ;
struct rx_ring_config {int num_rxd; } ;
struct rx_block_info {void* block_dma_addr; void* block_virt_addr; TYPE_5__* rxds; } ;
struct TYPE_12__ {int ring_len; scalar_t__ offset; scalar_t__ block_index; } ;
struct TYPE_11__ {int ring_len; scalar_t__ offset; scalar_t__ block_index; } ;
struct ring_info {int block_count; int pkt_cnt; int ring_no; struct buffAdd** ba; struct rx_block_info* rx_blocks; struct s2io_nic* nic; TYPE_4__ rx_curr_put_info; TYPE_3__ rx_curr_get_info; } ;
struct net_device {int name; } ;
struct list_info_hold {int dummy; } ;
struct TYPE_10__ {int fifo_len; scalar_t__ offset; } ;
struct TYPE_9__ {int fifo_len; scalar_t__ offset; } ;
struct fifo_info {int fifo_no; int /*<<< orphan*/  ufo_in_band_v; TYPE_8__* list_info; struct net_device* dev; scalar_t__ max_txds; struct s2io_nic* nic; TYPE_2__ tx_curr_get_info; TYPE_1__ tx_curr_put_info; } ;
struct buffAdd {void* ba_1; void* ba_1_org; void* ba_0; void* ba_0_org; } ;
struct TxD {int dummy; } ;
struct RxD_block {unsigned long reserved_2_pNext_RxD_block; scalar_t__ pNext_RxD_Blk_physical; } ;
struct RxD3 {int dummy; } ;
struct RxD1 {int dummy; } ;
typedef  void* dma_addr_t ;
struct TYPE_16__ {void* list_phy_addr; void* list_virt_addr; } ;
struct TYPE_15__ {int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {void* dma_addr; void* virt_addr; } ;

/* Variables and functions */
 unsigned long ALIGN_SIZE ; 
 unsigned long BUF0_LEN ; 
 unsigned long BUF1_LEN ; 
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERR_DBG ; 
 int FAILURE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO_DBG ; 
 int /*<<< orphan*/  INIT_DBG ; 
 int MAX_AVAILABLE_TXDS ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int PAGE_SIZE ; 
 size_t RXD_MODE_1 ; 
 size_t RXD_MODE_3B ; 
 int SIZE_OF_BLOCK ; 
 int SUCCESS ; 
 int TXD_MEM_PAGE_CNT (int,int) ; 
 int dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_8__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 void* pci_alloc_consistent (TYPE_7__*,int,void**) ; 
 int* rxd_count ; 
 int* rxd_size ; 

__attribute__((used)) static int init_shared_mem(struct s2io_nic *nic)
{
	u32 size;
	void *tmp_v_addr, *tmp_v_addr_next;
	dma_addr_t tmp_p_addr, tmp_p_addr_next;
	struct RxD_block *pre_rxd_blk = NULL;
	int i, j, blk_cnt;
	int lst_size, lst_per_page;
	struct net_device *dev = nic->dev;
	unsigned long tmp;
	struct buffAdd *ba;
	struct config_param *config = &nic->config;
	struct mac_info *mac_control = &nic->mac_control;
	unsigned long long mem_allocated = 0;

	/* Allocation and initialization of TXDLs in FIFOs */
	size = 0;
	for (i = 0; i < config->tx_fifo_num; i++) {
		struct tx_fifo_config *tx_cfg = &config->tx_cfg[i];

		size += tx_cfg->fifo_len;
	}
	if (size > MAX_AVAILABLE_TXDS) {
		DBG_PRINT(ERR_DBG,
			  "Too many TxDs requested: %d, max supported: %d\n",
			  size, MAX_AVAILABLE_TXDS);
		return -EINVAL;
	}

	size = 0;
	for (i = 0; i < config->tx_fifo_num; i++) {
		struct tx_fifo_config *tx_cfg = &config->tx_cfg[i];

		size = tx_cfg->fifo_len;
		/*
		 * Legal values are from 2 to 8192
		 */
		if (size < 2) {
			DBG_PRINT(ERR_DBG, "Fifo %d: Invalid length (%d) - "
				  "Valid lengths are 2 through 8192\n",
				  i, size);
			return -EINVAL;
		}
	}

	lst_size = (sizeof(struct TxD) * config->max_txds);
	lst_per_page = PAGE_SIZE / lst_size;

	for (i = 0; i < config->tx_fifo_num; i++) {
		struct fifo_info *fifo = &mac_control->fifos[i];
		struct tx_fifo_config *tx_cfg = &config->tx_cfg[i];
		int fifo_len = tx_cfg->fifo_len;
		int list_holder_size = fifo_len * sizeof(struct list_info_hold);

		fifo->list_info = kzalloc(list_holder_size, GFP_KERNEL);
		if (!fifo->list_info) {
			DBG_PRINT(INFO_DBG, "Malloc failed for list_info\n");
			return -ENOMEM;
		}
		mem_allocated += list_holder_size;
	}
	for (i = 0; i < config->tx_fifo_num; i++) {
		int page_num = TXD_MEM_PAGE_CNT(config->tx_cfg[i].fifo_len,
						lst_per_page);
		struct fifo_info *fifo = &mac_control->fifos[i];
		struct tx_fifo_config *tx_cfg = &config->tx_cfg[i];

		fifo->tx_curr_put_info.offset = 0;
		fifo->tx_curr_put_info.fifo_len = tx_cfg->fifo_len - 1;
		fifo->tx_curr_get_info.offset = 0;
		fifo->tx_curr_get_info.fifo_len = tx_cfg->fifo_len - 1;
		fifo->fifo_no = i;
		fifo->nic = nic;
		fifo->max_txds = MAX_SKB_FRAGS + 2;
		fifo->dev = dev;

		for (j = 0; j < page_num; j++) {
			int k = 0;
			dma_addr_t tmp_p;
			void *tmp_v;
			tmp_v = pci_alloc_consistent(nic->pdev,
						     PAGE_SIZE, &tmp_p);
			if (!tmp_v) {
				DBG_PRINT(INFO_DBG,
					  "pci_alloc_consistent failed for TxDL\n");
				return -ENOMEM;
			}
			/* If we got a zero DMA address(can happen on
			 * certain platforms like PPC), reallocate.
			 * Store virtual address of page we don't want,
			 * to be freed later.
			 */
			if (!tmp_p) {
				mac_control->zerodma_virt_addr = tmp_v;
				DBG_PRINT(INIT_DBG,
					  "%s: Zero DMA address for TxDL. "
					  "Virtual address %p\n",
					  dev->name, tmp_v);
				tmp_v = pci_alloc_consistent(nic->pdev,
							     PAGE_SIZE, &tmp_p);
				if (!tmp_v) {
					DBG_PRINT(INFO_DBG,
						  "pci_alloc_consistent failed for TxDL\n");
					return -ENOMEM;
				}
				mem_allocated += PAGE_SIZE;
			}
			while (k < lst_per_page) {
				int l = (j * lst_per_page) + k;
				if (l == tx_cfg->fifo_len)
					break;
				fifo->list_info[l].list_virt_addr =
					tmp_v + (k * lst_size);
				fifo->list_info[l].list_phy_addr =
					tmp_p + (k * lst_size);
				k++;
			}
		}
	}

	for (i = 0; i < config->tx_fifo_num; i++) {
		struct fifo_info *fifo = &mac_control->fifos[i];
		struct tx_fifo_config *tx_cfg = &config->tx_cfg[i];

		size = tx_cfg->fifo_len;
		fifo->ufo_in_band_v = kcalloc(size, sizeof(u64), GFP_KERNEL);
		if (!fifo->ufo_in_band_v)
			return -ENOMEM;
		mem_allocated += (size * sizeof(u64));
	}

	/* Allocation and initialization of RXDs in Rings */
	size = 0;
	for (i = 0; i < config->rx_ring_num; i++) {
		struct rx_ring_config *rx_cfg = &config->rx_cfg[i];
		struct ring_info *ring = &mac_control->rings[i];

		if (rx_cfg->num_rxd % (rxd_count[nic->rxd_mode] + 1)) {
			DBG_PRINT(ERR_DBG, "%s: Ring%d RxD count is not a "
				  "multiple of RxDs per Block\n",
				  dev->name, i);
			return FAILURE;
		}
		size += rx_cfg->num_rxd;
		ring->block_count = rx_cfg->num_rxd /
			(rxd_count[nic->rxd_mode] + 1);
		ring->pkt_cnt = rx_cfg->num_rxd - ring->block_count;
	}
	if (nic->rxd_mode == RXD_MODE_1)
		size = (size * (sizeof(struct RxD1)));
	else
		size = (size * (sizeof(struct RxD3)));

	for (i = 0; i < config->rx_ring_num; i++) {
		struct rx_ring_config *rx_cfg = &config->rx_cfg[i];
		struct ring_info *ring = &mac_control->rings[i];

		ring->rx_curr_get_info.block_index = 0;
		ring->rx_curr_get_info.offset = 0;
		ring->rx_curr_get_info.ring_len = rx_cfg->num_rxd - 1;
		ring->rx_curr_put_info.block_index = 0;
		ring->rx_curr_put_info.offset = 0;
		ring->rx_curr_put_info.ring_len = rx_cfg->num_rxd - 1;
		ring->nic = nic;
		ring->ring_no = i;

		blk_cnt = rx_cfg->num_rxd / (rxd_count[nic->rxd_mode] + 1);
		/*  Allocating all the Rx blocks */
		for (j = 0; j < blk_cnt; j++) {
			struct rx_block_info *rx_blocks;
			int l;

			rx_blocks = &ring->rx_blocks[j];
			size = SIZE_OF_BLOCK;	/* size is always page size */
			tmp_v_addr = pci_alloc_consistent(nic->pdev, size,
							  &tmp_p_addr);
			if (tmp_v_addr == NULL) {
				/*
				 * In case of failure, free_shared_mem()
				 * is called, which should free any
				 * memory that was alloced till the
				 * failure happened.
				 */
				rx_blocks->block_virt_addr = tmp_v_addr;
				return -ENOMEM;
			}
			mem_allocated += size;
			memset(tmp_v_addr, 0, size);

			size = sizeof(struct rxd_info) *
				rxd_count[nic->rxd_mode];
			rx_blocks->block_virt_addr = tmp_v_addr;
			rx_blocks->block_dma_addr = tmp_p_addr;
			rx_blocks->rxds = kmalloc(size,  GFP_KERNEL);
			if (!rx_blocks->rxds)
				return -ENOMEM;
			mem_allocated += size;
			for (l = 0; l < rxd_count[nic->rxd_mode]; l++) {
				rx_blocks->rxds[l].virt_addr =
					rx_blocks->block_virt_addr +
					(rxd_size[nic->rxd_mode] * l);
				rx_blocks->rxds[l].dma_addr =
					rx_blocks->block_dma_addr +
					(rxd_size[nic->rxd_mode] * l);
			}
		}
		/* Interlinking all Rx Blocks */
		for (j = 0; j < blk_cnt; j++) {
			int next = (j + 1) % blk_cnt;
			tmp_v_addr = ring->rx_blocks[j].block_virt_addr;
			tmp_v_addr_next = ring->rx_blocks[next].block_virt_addr;
			tmp_p_addr = ring->rx_blocks[j].block_dma_addr;
			tmp_p_addr_next = ring->rx_blocks[next].block_dma_addr;

			pre_rxd_blk = (struct RxD_block *)tmp_v_addr;
			pre_rxd_blk->reserved_2_pNext_RxD_block =
				(unsigned long)tmp_v_addr_next;
			pre_rxd_blk->pNext_RxD_Blk_physical =
				(u64)tmp_p_addr_next;
		}
	}
	if (nic->rxd_mode == RXD_MODE_3B) {
		/*
		 * Allocation of Storages for buffer addresses in 2BUFF mode
		 * and the buffers as well.
		 */
		for (i = 0; i < config->rx_ring_num; i++) {
			struct rx_ring_config *rx_cfg = &config->rx_cfg[i];
			struct ring_info *ring = &mac_control->rings[i];

			blk_cnt = rx_cfg->num_rxd /
				(rxd_count[nic->rxd_mode] + 1);
			size = sizeof(struct buffAdd *) * blk_cnt;
			ring->ba = kmalloc(size, GFP_KERNEL);
			if (!ring->ba)
				return -ENOMEM;
			mem_allocated += size;
			for (j = 0; j < blk_cnt; j++) {
				int k = 0;

				size = sizeof(struct buffAdd) *
					(rxd_count[nic->rxd_mode] + 1);
				ring->ba[j] = kmalloc(size, GFP_KERNEL);
				if (!ring->ba[j])
					return -ENOMEM;
				mem_allocated += size;
				while (k != rxd_count[nic->rxd_mode]) {
					ba = &ring->ba[j][k];
					size = BUF0_LEN + ALIGN_SIZE;
					ba->ba_0_org = kmalloc(size, GFP_KERNEL);
					if (!ba->ba_0_org)
						return -ENOMEM;
					mem_allocated += size;
					tmp = (unsigned long)ba->ba_0_org;
					tmp += ALIGN_SIZE;
					tmp &= ~((unsigned long)ALIGN_SIZE);
					ba->ba_0 = (void *)tmp;

					size = BUF1_LEN + ALIGN_SIZE;
					ba->ba_1_org = kmalloc(size, GFP_KERNEL);
					if (!ba->ba_1_org)
						return -ENOMEM;
					mem_allocated += size;
					tmp = (unsigned long)ba->ba_1_org;
					tmp += ALIGN_SIZE;
					tmp &= ~((unsigned long)ALIGN_SIZE);
					ba->ba_1 = (void *)tmp;
					k++;
				}
			}
		}
	}

	/* Allocation and initialization of Statistics block */
	size = sizeof(struct stat_block);
	mac_control->stats_mem =
		pci_alloc_consistent(nic->pdev, size,
				     &mac_control->stats_mem_phy);

	if (!mac_control->stats_mem) {
		/*
		 * In case of failure, free_shared_mem() is called, which
		 * should free any memory that was alloced till the
		 * failure happened.
		 */
		return -ENOMEM;
	}
	mem_allocated += size;
	mac_control->stats_mem_sz = size;

	tmp_v_addr = mac_control->stats_mem;
	mac_control->stats_info = (struct stat_block *)tmp_v_addr;
	memset(tmp_v_addr, 0, size);
	DBG_PRINT(INIT_DBG, "%s: Ring Mem PHY: 0x%llx\n",
		dev_name(&nic->pdev->dev), (unsigned long long)tmp_p_addr);
	mac_control->stats_info->sw_stat.mem_allocated += mem_allocated;
	return SUCCESS;
}