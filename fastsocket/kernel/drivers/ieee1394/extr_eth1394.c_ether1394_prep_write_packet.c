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
typedef  int u64 ;
struct hpsb_packet {int node_id; int tcode; int header_size; int expect_response; int* header; int tlabel; int data_size; void* data; } ;
struct hpsb_host {int node_id; } ;
typedef  int nodeid_t ;

/* Variables and functions */
 int EAGAIN ; 
 int TCODE_WRITEB ; 
 scalar_t__ hpsb_get_tlabel (struct hpsb_packet*) ; 

__attribute__((used)) static int ether1394_prep_write_packet(struct hpsb_packet *p,
				       struct hpsb_host *host, nodeid_t node,
				       u64 addr, void *data, int tx_len)
{
	p->node_id = node;

	if (hpsb_get_tlabel(p))
		return -EAGAIN;

	p->tcode = TCODE_WRITEB;
	p->header_size = 16;
	p->expect_response = 1;
	p->header[0] =
		p->node_id << 16 | p->tlabel << 10 | 1 << 8 | TCODE_WRITEB << 4;
	p->header[1] = host->node_id << 16 | addr >> 32;
	p->header[2] = addr & 0xffffffff;
	p->header[3] = tx_len << 16;
	p->data_size = (tx_len + 3) & ~3;
	p->data = data;

	return 0;
}