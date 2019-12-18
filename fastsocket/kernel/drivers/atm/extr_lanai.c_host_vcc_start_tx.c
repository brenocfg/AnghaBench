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
struct TYPE_10__ {int dmaaddr; } ;
struct TYPE_9__ {TYPE_5__ buf; TYPE_3__* atmvcc; } ;
struct lanai_vcc {int vci; TYPE_4__ tx; } ;
typedef  int dma_addr_t ;
struct TYPE_6__ {scalar_t__ traffic_class; } ;
struct TYPE_7__ {TYPE_1__ txtp; } ;
struct TYPE_8__ {TYPE_2__ qos; } ;

/* Variables and functions */
 scalar_t__ ATM_CBR ; 
 int TXADDR1_SET_SIZE (int /*<<< orphan*/ ) ; 
 int TXCBR_NEXT_BOZO ; 
 int /*<<< orphan*/  cardvcc_write (struct lanai_vcc const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lanai_buf_size_cardorder (TYPE_5__*) ; 
 int /*<<< orphan*/  vcc_txaddr1 ; 
 int /*<<< orphan*/  vcc_txaddr2 ; 
 int /*<<< orphan*/  vcc_txcbr_next ; 
 int /*<<< orphan*/  vcc_txcrc1 ; 
 int /*<<< orphan*/  vcc_txcrc2 ; 
 int /*<<< orphan*/  vcc_txendptr ; 
 int /*<<< orphan*/  vcc_txicg ; 
 int /*<<< orphan*/  vcc_txreadptr ; 
 int /*<<< orphan*/  vcc_txwriteptr ; 

__attribute__((used)) static void host_vcc_start_tx(const struct lanai_vcc *lvcc)
{
	dma_addr_t dmaaddr = lvcc->tx.buf.dmaaddr;
	cardvcc_write(lvcc, 0, vcc_txicg);
	cardvcc_write(lvcc, 0xFFFF, vcc_txcrc1);
	cardvcc_write(lvcc, 0xFFFF, vcc_txcrc2);
	cardvcc_write(lvcc, 0, vcc_txreadptr);
	cardvcc_write(lvcc, 0, vcc_txendptr);
	cardvcc_write(lvcc, 0, vcc_txwriteptr);
	cardvcc_write(lvcc,
		(lvcc->tx.atmvcc->qos.txtp.traffic_class == ATM_CBR) ?
		TXCBR_NEXT_BOZO | lvcc->vci : 0, vcc_txcbr_next);
	cardvcc_write(lvcc, (dmaaddr >> 16) & 0xFFFF, vcc_txaddr2);
	cardvcc_write(lvcc,
	    ((dmaaddr >> 8) & 0xFF) |
	    TXADDR1_SET_SIZE(lanai_buf_size_cardorder(&lvcc->tx.buf)),
	    vcc_txaddr1);
}