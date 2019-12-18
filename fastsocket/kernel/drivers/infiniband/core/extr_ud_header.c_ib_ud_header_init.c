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
typedef  int u16 ;
struct TYPE_8__ {int pad_count; scalar_t__ transport_header_version; int /*<<< orphan*/  opcode; } ;
struct TYPE_7__ {int ip_version; int next_header; void* payload_length; } ;
struct TYPE_6__ {void* type; } ;
struct TYPE_5__ {void* packet_length; int /*<<< orphan*/  link_next_header; scalar_t__ link_version; } ;
struct ib_ud_header {int lrh_present; int eth_present; int vlan_present; int grh_present; int immediate_present; TYPE_4__ bth; TYPE_3__ grh; TYPE_2__ eth; TYPE_1__ lrh; } ;

/* Variables and functions */
 int ETH_P_8021Q ; 
 int IB_BTH_BYTES ; 
 int IB_DETH_BYTES ; 
 int IB_GRH_BYTES ; 
 int /*<<< orphan*/  IB_LNH_IBA_GLOBAL ; 
 int /*<<< orphan*/  IB_LNH_IBA_LOCAL ; 
 int IB_LRH_BYTES ; 
 int /*<<< orphan*/  IB_OPCODE_UD_SEND_ONLY ; 
 int /*<<< orphan*/  IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memset (struct ib_ud_header*,int /*<<< orphan*/ ,int) ; 

void ib_ud_header_init(int     		    payload_bytes,
		       int		    lrh_present,
		       int		    eth_present,
		       int		    vlan_present,
		       int    		    grh_present,
		       int		    immediate_present,
		       struct ib_ud_header *header)
{
	memset(header, 0, sizeof *header);

	if (lrh_present) {
		u16 packet_length;

		header->lrh.link_version     = 0;
		header->lrh.link_next_header =
			grh_present ? IB_LNH_IBA_GLOBAL : IB_LNH_IBA_LOCAL;
		packet_length = (IB_LRH_BYTES	+
				 IB_BTH_BYTES	+
				 IB_DETH_BYTES	+
				 (grh_present ? IB_GRH_BYTES : 0) +
				 payload_bytes	+
				 4		+ /* ICRC     */
				 3) / 4;	  /* round up */
		header->lrh.packet_length = cpu_to_be16(packet_length);
	}

	if (vlan_present)
		header->eth.type = cpu_to_be16(ETH_P_8021Q);

	if (grh_present) {
		header->grh.ip_version      = 6;
		header->grh.payload_length  =
			cpu_to_be16((IB_BTH_BYTES     +
				     IB_DETH_BYTES    +
				     payload_bytes    +
				     4                + /* ICRC     */
				     3) & ~3);          /* round up */
		header->grh.next_header     = 0x1b;
	}

	if (immediate_present)
		header->bth.opcode           = IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE;
	else
		header->bth.opcode           = IB_OPCODE_UD_SEND_ONLY;
	header->bth.pad_count                = (4 - payload_bytes) & 3;
	header->bth.transport_header_version = 0;

	header->lrh_present = lrh_present;
	header->eth_present = eth_present;
	header->vlan_present = vlan_present;
	header->grh_present = grh_present;
	header->immediate_present = immediate_present;
}