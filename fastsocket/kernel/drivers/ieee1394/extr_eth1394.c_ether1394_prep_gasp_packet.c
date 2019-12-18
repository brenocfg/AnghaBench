#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct hpsb_packet {int header_size; int tcode; int* header; int data_size; int node_id; int /*<<< orphan*/  speed_code; void** data; } ;
struct eth1394_priv {int broadcast_channel; int /*<<< orphan*/  bc_sspd; TYPE_1__* host; } ;
typedef  void* quadlet_t ;
struct TYPE_2__ {int node_id; } ;

/* Variables and functions */
 int ALL_NODES ; 
 int ETHER1394_GASP_SPECIFIER_ID_HI ; 
 int ETHER1394_GASP_SPECIFIER_ID_LO ; 
 int ETHER1394_GASP_VERSION ; 
 int LOCAL_BUS ; 
 int TCODE_STREAM_DATA ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static void ether1394_prep_gasp_packet(struct hpsb_packet *p,
				       struct eth1394_priv *priv,
				       struct sk_buff *skb, int length)
{
	p->header_size = 4;
	p->tcode = TCODE_STREAM_DATA;

	p->header[0] = length << 16 | 3 << 14 | priv->broadcast_channel << 8 |
		       TCODE_STREAM_DATA << 4;
	p->data_size = length;
	p->data = (quadlet_t *)skb->data - 2;
	p->data[0] = cpu_to_be32(priv->host->node_id << 16 |
				 ETHER1394_GASP_SPECIFIER_ID_HI);
	p->data[1] = cpu_to_be32(ETHER1394_GASP_SPECIFIER_ID_LO << 24 |
				 ETHER1394_GASP_VERSION);

	p->speed_code = priv->bc_sspd;

	/* prevent hpsb_send_packet() from overriding our speed code */
	p->node_id = LOCAL_BUS | ALL_NODES;
}