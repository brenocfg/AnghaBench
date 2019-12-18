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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {TYPE_8__* rx; TYPE_6__* bcn; TYPE_4__* atim; TYPE_2__* tx; } ;
struct queue_entry_priv_mmio {int /*<<< orphan*/  desc_dma; } ;
struct TYPE_16__ {TYPE_7__* entries; int /*<<< orphan*/  limit; int /*<<< orphan*/  desc_size; } ;
struct TYPE_15__ {struct queue_entry_priv_mmio* priv_data; } ;
struct TYPE_14__ {TYPE_5__* entries; } ;
struct TYPE_13__ {struct queue_entry_priv_mmio* priv_data; } ;
struct TYPE_12__ {TYPE_3__* entries; int /*<<< orphan*/  limit; } ;
struct TYPE_11__ {struct queue_entry_priv_mmio* priv_data; } ;
struct TYPE_10__ {TYPE_1__* entries; int /*<<< orphan*/  limit; int /*<<< orphan*/  desc_size; } ;
struct TYPE_9__ {struct queue_entry_priv_mmio* priv_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXCSR1 ; 
 int /*<<< orphan*/  RXCSR1_NUM_RXD ; 
 int /*<<< orphan*/  RXCSR1_RXD_SIZE ; 
 int /*<<< orphan*/  RXCSR2 ; 
 int /*<<< orphan*/  RXCSR2_RX_RING_REGISTER ; 
 int /*<<< orphan*/  TXCSR2 ; 
 int /*<<< orphan*/  TXCSR2_NUM_ATIM ; 
 int /*<<< orphan*/  TXCSR2_NUM_PRIO ; 
 int /*<<< orphan*/  TXCSR2_NUM_TXD ; 
 int /*<<< orphan*/  TXCSR2_TXD_SIZE ; 
 int /*<<< orphan*/  TXCSR3 ; 
 int /*<<< orphan*/  TXCSR3_TX_RING_REGISTER ; 
 int /*<<< orphan*/  TXCSR4 ; 
 int /*<<< orphan*/  TXCSR4_ATIM_RING_REGISTER ; 
 int /*<<< orphan*/  TXCSR5 ; 
 int /*<<< orphan*/  TXCSR5_PRIO_RING_REGISTER ; 
 int /*<<< orphan*/  TXCSR6 ; 
 int /*<<< orphan*/  TXCSR6_BEACON_RING_REGISTER ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2500pci_init_queues(struct rt2x00_dev *rt2x00dev)
{
	struct queue_entry_priv_mmio *entry_priv;
	u32 reg;

	/*
	 * Initialize registers.
	 */
	rt2x00mmio_register_read(rt2x00dev, TXCSR2, &reg);
	rt2x00_set_field32(&reg, TXCSR2_TXD_SIZE, rt2x00dev->tx[0].desc_size);
	rt2x00_set_field32(&reg, TXCSR2_NUM_TXD, rt2x00dev->tx[1].limit);
	rt2x00_set_field32(&reg, TXCSR2_NUM_ATIM, rt2x00dev->atim->limit);
	rt2x00_set_field32(&reg, TXCSR2_NUM_PRIO, rt2x00dev->tx[0].limit);
	rt2x00mmio_register_write(rt2x00dev, TXCSR2, reg);

	entry_priv = rt2x00dev->tx[1].entries[0].priv_data;
	rt2x00mmio_register_read(rt2x00dev, TXCSR3, &reg);
	rt2x00_set_field32(&reg, TXCSR3_TX_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_register_write(rt2x00dev, TXCSR3, reg);

	entry_priv = rt2x00dev->tx[0].entries[0].priv_data;
	rt2x00mmio_register_read(rt2x00dev, TXCSR5, &reg);
	rt2x00_set_field32(&reg, TXCSR5_PRIO_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_register_write(rt2x00dev, TXCSR5, reg);

	entry_priv = rt2x00dev->atim->entries[0].priv_data;
	rt2x00mmio_register_read(rt2x00dev, TXCSR4, &reg);
	rt2x00_set_field32(&reg, TXCSR4_ATIM_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_register_write(rt2x00dev, TXCSR4, reg);

	entry_priv = rt2x00dev->bcn->entries[0].priv_data;
	rt2x00mmio_register_read(rt2x00dev, TXCSR6, &reg);
	rt2x00_set_field32(&reg, TXCSR6_BEACON_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_register_write(rt2x00dev, TXCSR6, reg);

	rt2x00mmio_register_read(rt2x00dev, RXCSR1, &reg);
	rt2x00_set_field32(&reg, RXCSR1_RXD_SIZE, rt2x00dev->rx->desc_size);
	rt2x00_set_field32(&reg, RXCSR1_NUM_RXD, rt2x00dev->rx->limit);
	rt2x00mmio_register_write(rt2x00dev, RXCSR1, reg);

	entry_priv = rt2x00dev->rx->entries[0].priv_data;
	rt2x00mmio_register_read(rt2x00dev, RXCSR2, &reg);
	rt2x00_set_field32(&reg, RXCSR2_RX_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_register_write(rt2x00dev, RXCSR2, reg);

	return 0;
}