#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ti_pcl {int pcl_status; } ;
struct TYPE_8__ {int /*<<< orphan*/  next; } ;
struct TYPE_7__ {int /*<<< orphan*/  queue_lock; TYPE_4__ queue; int /*<<< orphan*/  data_dma; int /*<<< orphan*/  header_dma; TYPE_4__ pcl_queue; int /*<<< orphan*/  pcl; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue_lock; TYPE_4__ queue; int /*<<< orphan*/  data_dma; int /*<<< orphan*/  header_dma; TYPE_4__ pcl_queue; int /*<<< orphan*/  pcl; } ;
struct TYPE_5__ {size_t next; int last; int /*<<< orphan*/  tq; int /*<<< orphan*/  lock; int /*<<< orphan*/  pcl_start; int /*<<< orphan*/  chan_count; int /*<<< orphan*/  used; void** stat; } ;
struct ti_lynx {int selfid_size; int phy_reg0; int* rcv_page; int /*<<< orphan*/  rcv_pcl_start; int /*<<< orphan*/  id; TYPE_3__ iso_send; int /*<<< orphan*/  dev; TYPE_2__ async; TYPE_1__ iso_rcv; int /*<<< orphan*/  phy_reg_lock; struct hpsb_host* host; } ;
struct hpsb_packet {scalar_t__ data_size; scalar_t__ header_size; int /*<<< orphan*/  driver_list; } ;
struct hpsb_host {scalar_t__ in_bus_reset; } ;
typedef  int quadlet_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ACKX_SEND_ERROR ; 
 int ACKX_TIMEOUT ; 
 int /*<<< orphan*/  CHANNEL_ASYNC_RCV ; 
 int /*<<< orphan*/  CHANNEL_ASYNC_SEND ; 
 int /*<<< orphan*/  CHANNEL_ISO_RCV ; 
 int /*<<< orphan*/  CHANNEL_ISO_SEND ; 
 int /*<<< orphan*/  DMA_CHAN_STAT (int /*<<< orphan*/ ) ; 
 int DMA_CHAN_STAT_PKTCMPL ; 
 int DMA_CHAN_STAT_SELFID ; 
 int DMA_CHAN_STAT_SPECIALACK ; 
 int /*<<< orphan*/  DMA_WORD1_CMP_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIFO_CONTROL ; 
 int FIFO_CONTROL_GRF_FLUSH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int LINK_INT_ASYNC_STUCK ; 
 int LINK_INT_ATF_UNDERFLOW ; 
 int LINK_INT_GRF_OVERFLOW ; 
 int LINK_INT_ISO_STUCK ; 
 int LINK_INT_ITF_UNDERFLOW ; 
 int LINK_INT_PHY_BUSRESET ; 
 int LINK_INT_PHY_REG_RCVD ; 
 int LINK_INT_PHY_TIMEOUT ; 
 int LINK_INT_SENT_REJECT ; 
 int /*<<< orphan*/  LINK_INT_STATUS ; 
 int LINK_INT_TX_INVALID_TC ; 
 int /*<<< orphan*/  LINK_PHY ; 
 int NUM_ISORCV_PCL ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int PCI_INT_1394 ; 
 int PCI_INT_DMA_HLT (int /*<<< orphan*/ ) ; 
 int PCI_INT_INT_PEND ; 
 int /*<<< orphan*/  PCI_INT_STATUS ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PRINTD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int TCODE_READQ_RESPONSE ; 
 int TCODE_WRITEQ ; 
 int /*<<< orphan*/  cpu_to_be32s (int*) ; 
 struct hpsb_packet* driver_packet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pcl (struct ti_lynx*,int /*<<< orphan*/ ,struct ti_pcl*) ; 
 int /*<<< orphan*/  handle_selfid (struct ti_lynx*,struct hpsb_host*) ; 
 int /*<<< orphan*/  hpsb_async ; 
 int /*<<< orphan*/  hpsb_bus_reset (struct hpsb_host*) ; 
 int /*<<< orphan*/  hpsb_iso ; 
 int /*<<< orphan*/  hpsb_packet_received (struct hpsb_host*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsb_packet_sent (struct hpsb_host*,struct hpsb_packet*,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (TYPE_4__*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 void* reg_read (struct ti_lynx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct ti_lynx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  run_pcl (struct ti_lynx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_sub_pcl (struct ti_lynx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_next (struct ti_lynx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t lynx_irq_handler(int irq, void *dev_id)
{
        struct ti_lynx *lynx = (struct ti_lynx *)dev_id;
        struct hpsb_host *host = lynx->host;
        u32 intmask;
        u32 linkint;

        linkint = reg_read(lynx, LINK_INT_STATUS);
        intmask = reg_read(lynx, PCI_INT_STATUS);

        if (!(intmask & PCI_INT_INT_PEND))
		return IRQ_NONE;

        PRINTD(KERN_DEBUG, lynx->id, "interrupt: 0x%08x / 0x%08x", intmask,
               linkint);

        reg_write(lynx, LINK_INT_STATUS, linkint);
        reg_write(lynx, PCI_INT_STATUS, intmask);

        if (intmask & PCI_INT_1394) {
                if (linkint & LINK_INT_PHY_TIMEOUT) {
                        PRINT(KERN_INFO, lynx->id, "PHY timeout occurred");
                }
                if (linkint & LINK_INT_PHY_BUSRESET) {
                        PRINT(KERN_INFO, lynx->id, "bus reset interrupt");
                        lynx->selfid_size = -1;
                        lynx->phy_reg0 = -1;
                        if (!host->in_bus_reset)
                                hpsb_bus_reset(host);
                }
                if (linkint & LINK_INT_PHY_REG_RCVD) {
                        u32 reg;

                        spin_lock(&lynx->phy_reg_lock);
                        reg = reg_read(lynx, LINK_PHY);
                        spin_unlock(&lynx->phy_reg_lock);

                        if (!host->in_bus_reset) {
                                PRINT(KERN_INFO, lynx->id,
                                      "phy reg received without reset");
                        } else if (reg & 0xf00) {
                                PRINT(KERN_INFO, lynx->id,
                                      "unsolicited phy reg %d received",
                                      (reg >> 8) & 0xf);
                        } else {
                                lynx->phy_reg0 = reg & 0xff;
                                handle_selfid(lynx, host);
                        }
                }
                if (linkint & LINK_INT_ISO_STUCK) {
                        PRINT(KERN_INFO, lynx->id, "isochronous transmitter stuck");
                }
                if (linkint & LINK_INT_ASYNC_STUCK) {
                        PRINT(KERN_INFO, lynx->id, "asynchronous transmitter stuck");
                }
                if (linkint & LINK_INT_SENT_REJECT) {
                        PRINT(KERN_INFO, lynx->id, "sent reject");
                }
                if (linkint & LINK_INT_TX_INVALID_TC) {
                        PRINT(KERN_INFO, lynx->id, "invalid transaction code");
                }
                if (linkint & LINK_INT_GRF_OVERFLOW) {
                        /* flush FIFO if overflow happens during reset */
                        if (host->in_bus_reset)
                                reg_write(lynx, FIFO_CONTROL,
                                          FIFO_CONTROL_GRF_FLUSH);
                        PRINT(KERN_INFO, lynx->id, "GRF overflow");
                }
                if (linkint & LINK_INT_ITF_UNDERFLOW) {
                        PRINT(KERN_INFO, lynx->id, "ITF underflow");
                }
                if (linkint & LINK_INT_ATF_UNDERFLOW) {
                        PRINT(KERN_INFO, lynx->id, "ATF underflow");
                }
        }

        if (intmask & PCI_INT_DMA_HLT(CHANNEL_ISO_RCV)) {
                PRINTD(KERN_DEBUG, lynx->id, "iso receive");

                spin_lock(&lynx->iso_rcv.lock);

                lynx->iso_rcv.stat[lynx->iso_rcv.next] =
                        reg_read(lynx, DMA_CHAN_STAT(CHANNEL_ISO_RCV));

                lynx->iso_rcv.used++;
                lynx->iso_rcv.next = (lynx->iso_rcv.next + 1) % NUM_ISORCV_PCL;

                if ((lynx->iso_rcv.next == lynx->iso_rcv.last)
                    || !lynx->iso_rcv.chan_count) {
                        PRINTD(KERN_DEBUG, lynx->id, "stopped");
                        reg_write(lynx, DMA_WORD1_CMP_ENABLE(CHANNEL_ISO_RCV), 0);
                }

                run_sub_pcl(lynx, lynx->iso_rcv.pcl_start, lynx->iso_rcv.next,
                            CHANNEL_ISO_RCV);

                spin_unlock(&lynx->iso_rcv.lock);

		tasklet_schedule(&lynx->iso_rcv.tq);
        }

        if (intmask & PCI_INT_DMA_HLT(CHANNEL_ASYNC_SEND)) {
                PRINTD(KERN_DEBUG, lynx->id, "async sent");
                spin_lock(&lynx->async.queue_lock);

                if (list_empty(&lynx->async.pcl_queue)) {
                        spin_unlock(&lynx->async.queue_lock);
                        PRINT(KERN_WARNING, lynx->id, "async dma halted, but no queued packet (maybe it was cancelled)");
                } else {
                        struct ti_pcl pcl;
                        u32 ack;
                        struct hpsb_packet *packet;

                        get_pcl(lynx, lynx->async.pcl, &pcl);

                        packet = driver_packet(lynx->async.pcl_queue.next);
                        list_del_init(&packet->driver_list);

                        pci_unmap_single(lynx->dev, lynx->async.header_dma,
                                         packet->header_size, PCI_DMA_TODEVICE);
                        if (packet->data_size) {
                                pci_unmap_single(lynx->dev, lynx->async.data_dma,
                                                 packet->data_size, PCI_DMA_TODEVICE);
                        }

                        if (!list_empty(&lynx->async.queue)) {
                                send_next(lynx, hpsb_async);
                        }

                        spin_unlock(&lynx->async.queue_lock);

                        if (pcl.pcl_status & DMA_CHAN_STAT_PKTCMPL) {
                                if (pcl.pcl_status & DMA_CHAN_STAT_SPECIALACK) {
                                        ack = (pcl.pcl_status >> 15) & 0xf;
                                        PRINTD(KERN_INFO, lynx->id, "special ack %d", ack);
                                        ack = (ack == 1 ? ACKX_TIMEOUT : ACKX_SEND_ERROR);
                                } else {
                                        ack = (pcl.pcl_status >> 15) & 0xf;
                                }
                        } else {
                                PRINT(KERN_INFO, lynx->id, "async packet was not completed");
                                ack = ACKX_SEND_ERROR;
                        }
                        hpsb_packet_sent(host, packet, ack);
                }
        }

        if (intmask & PCI_INT_DMA_HLT(CHANNEL_ISO_SEND)) {
                PRINTD(KERN_DEBUG, lynx->id, "iso sent");
                spin_lock(&lynx->iso_send.queue_lock);

                if (list_empty(&lynx->iso_send.pcl_queue)) {
                        spin_unlock(&lynx->iso_send.queue_lock);
                        PRINT(KERN_ERR, lynx->id, "iso send dma halted, but no queued packet");
                } else {
                        struct ti_pcl pcl;
                        u32 ack;
                        struct hpsb_packet *packet;

                        get_pcl(lynx, lynx->iso_send.pcl, &pcl);

                        packet = driver_packet(lynx->iso_send.pcl_queue.next);
                        list_del_init(&packet->driver_list);

                        pci_unmap_single(lynx->dev, lynx->iso_send.header_dma,
                                         packet->header_size, PCI_DMA_TODEVICE);
                        if (packet->data_size) {
                                pci_unmap_single(lynx->dev, lynx->iso_send.data_dma,
                                                 packet->data_size, PCI_DMA_TODEVICE);
                        }
#if 0 /* has been removed from ieee1394 core */
                        if (!list_empty(&lynx->iso_send.queue)) {
                                send_next(lynx, hpsb_iso);
                        }
#endif
                        spin_unlock(&lynx->iso_send.queue_lock);

                        if (pcl.pcl_status & DMA_CHAN_STAT_PKTCMPL) {
                                if (pcl.pcl_status & DMA_CHAN_STAT_SPECIALACK) {
                                        ack = (pcl.pcl_status >> 15) & 0xf;
                                        PRINTD(KERN_INFO, lynx->id, "special ack %d", ack);
                                        ack = (ack == 1 ? ACKX_TIMEOUT : ACKX_SEND_ERROR);
                                } else {
                                        ack = (pcl.pcl_status >> 15) & 0xf;
                                }
                        } else {
                                PRINT(KERN_INFO, lynx->id, "iso send packet was not completed");
                                ack = ACKX_SEND_ERROR;
                        }

                        hpsb_packet_sent(host, packet, ack); //FIXME: maybe we should just use ACK_COMPLETE and ACKX_SEND_ERROR
                }
        }

        if (intmask & PCI_INT_DMA_HLT(CHANNEL_ASYNC_RCV)) {
                /* general receive DMA completed */
                int stat = reg_read(lynx, DMA_CHAN_STAT(CHANNEL_ASYNC_RCV));

                PRINTD(KERN_DEBUG, lynx->id, "received packet size %d",
                       stat & 0x1fff);

                if (stat & DMA_CHAN_STAT_SELFID) {
                        lynx->selfid_size = stat & 0x1fff;
                        handle_selfid(lynx, host);
                } else {
                        quadlet_t *q_data = lynx->rcv_page;
                        if ((*q_data >> 4 & 0xf) == TCODE_READQ_RESPONSE
                            || (*q_data >> 4 & 0xf) == TCODE_WRITEQ) {
                                cpu_to_be32s(q_data + 3);
                        }
                        hpsb_packet_received(host, q_data, stat & 0x1fff, 0);
                }

                run_pcl(lynx, lynx->rcv_pcl_start, CHANNEL_ASYNC_RCV);
        }

	return IRQ_HANDLED;
}