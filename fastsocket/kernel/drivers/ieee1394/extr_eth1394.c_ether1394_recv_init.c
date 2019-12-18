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
struct eth1394_priv {int /*<<< orphan*/  bc_state; int /*<<< orphan*/ * iso; int /*<<< orphan*/  broadcast_channel; TYPE_2__* host; } ;
struct TYPE_3__ {int max_rec; } ;
struct TYPE_4__ {TYPE_1__ csr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  ETH1394_PRINT_G (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ETHER1394_BC_ERROR ; 
 int /*<<< orphan*/  ETHER1394_BC_RUNNING ; 
 int /*<<< orphan*/  ETHER1394_BC_STOPPED ; 
 unsigned int ETHER1394_GASP_BUFFERS ; 
 int /*<<< orphan*/  HPSB_ISO_DMA_PACKET_PER_BUFFER ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  ether1394_iso ; 
 int /*<<< orphan*/ * hpsb_iso_recv_init (TYPE_2__*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ hpsb_iso_recv_start (int /*<<< orphan*/ *,int,int,int) ; 
 unsigned int min (unsigned int,int) ; 

__attribute__((used)) static int ether1394_recv_init(struct eth1394_priv *priv)
{
	unsigned int iso_buf_size;

	/* FIXME: rawiso limits us to PAGE_SIZE */
	iso_buf_size = min((unsigned int)PAGE_SIZE,
			   2 * (1U << (priv->host->csr.max_rec + 1)));

	priv->iso = hpsb_iso_recv_init(priv->host,
				       ETHER1394_GASP_BUFFERS * iso_buf_size,
				       ETHER1394_GASP_BUFFERS,
				       priv->broadcast_channel,
				       HPSB_ISO_DMA_PACKET_PER_BUFFER,
				       1, ether1394_iso);
	if (priv->iso == NULL) {
		ETH1394_PRINT_G(KERN_ERR, "Failed to allocate IR context\n");
		priv->bc_state = ETHER1394_BC_ERROR;
		return -EAGAIN;
	}

	if (hpsb_iso_recv_start(priv->iso, -1, (1 << 3), -1) < 0)
		priv->bc_state = ETHER1394_BC_STOPPED;
	else
		priv->bc_state = ETHER1394_BC_RUNNING;
	return 0;
}