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
typedef  int u8_t ;
struct pbuf {int /*<<< orphan*/  tot_len; scalar_t__ payload; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  HCI_HC_BB_OGF ; 
 int /*<<< orphan*/  HCI_SET_HC_TO_H_FC_OCF ; 
 int /*<<< orphan*/  HCI_SET_HC_TO_H_FC_PLEN ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 struct pbuf* hci_cmd_ass (struct pbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physbusif_output (struct pbuf*,int /*<<< orphan*/ ) ; 

err_t hci_set_hc_to_h_fc(void)
{
	struct pbuf *p;

	if((p = btpbuf_alloc(PBUF_RAW, HCI_SET_HC_TO_H_FC_PLEN, PBUF_RAM)) == NULL) {
		ERROR("hci_set_hc_to_h_fc: Could not allocate memory for pbuf\n");
		return ERR_MEM;
	}
	/* Assembling command packet */
	p = hci_cmd_ass(p, HCI_SET_HC_TO_H_FC_OCF, HCI_HC_BB_OGF, HCI_SET_HC_TO_H_FC_PLEN);
	/* Assembling cmd prameters */
	((u8_t *)p->payload)[4] = 0x01; /* Flow control on for HCI ACL Data Packets and off for HCI
									 SCO Data Packets in direction from Host Controller to
				 Host */
	physbusif_output(p, p->tot_len);
	btpbuf_free(p);

	return ERR_OK;
}