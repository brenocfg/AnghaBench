#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int features; int map_size; int /*<<< orphan*/  pci_irq; scalar_t__ irq_mask; } ;
struct TYPE_7__ {int /*<<< orphan*/  event_lock; scalar_t__ events; TYPE_5__* dev; TYPE_1__ cap; } ;
typedef  TYPE_2__ vrc4173_socket_t ;
struct TYPE_8__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int BAT_DEAD_EN ; 
 int BAT_WAR_EN ; 
 int CARD_DT_EN ; 
 int /*<<< orphan*/  CARD_SCI ; 
 int /*<<< orphan*/  GLO_CNT ; 
 int RDY_EN ; 
 int SS_CAP_PAGE_REGS ; 
 int SS_CAP_PCCARD ; 
 int /*<<< orphan*/  cardu_pciregs_init (TYPE_5__*) ; 
 TYPE_2__* cardu_sockets ; 
 int /*<<< orphan*/  exca_writeb (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cardu_init(unsigned int slot)
{
	vrc4173_socket_t *socket = &cardu_sockets[slot];

	cardu_pciregs_init(socket->dev);

	/* CARD_SC bits are cleared by reading CARD_SC. */
	exca_writeb(socket, GLO_CNT, 0);

	socket->cap.features |= SS_CAP_PCCARD | SS_CAP_PAGE_REGS;
	socket->cap.irq_mask = 0;
	socket->cap.map_size = 0x1000;
	socket->cap.pci_irq  = socket->dev->irq;
	socket->events = 0;
	spin_lock_init(socket->event_lock);

	/* Enable PC Card status interrupts */
	exca_writeb(socket, CARD_SCI, CARD_DT_EN|RDY_EN|BAT_WAR_EN|BAT_DEAD_EN);

	return 0;
}