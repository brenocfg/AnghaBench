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
struct bd_addr {int* addr; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  HCI_LINK_CTRL_OGF ; 
 int /*<<< orphan*/  HCI_PIN_CODE_REQ_REP ; 
 int /*<<< orphan*/  HCI_PIN_CODE_REQ_REP_PLEN ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 struct pbuf* hci_cmd_ass (struct pbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physbusif_output (struct pbuf*,int /*<<< orphan*/ ) ; 

err_t hci_pin_code_request_reply(struct bd_addr *bdaddr, u8_t pinlen, u8_t *pincode)
{
	struct pbuf *p;

	if((p = btpbuf_alloc(PBUF_RAW, HCI_PIN_CODE_REQ_REP_PLEN, PBUF_RAM)) == NULL) {
		ERROR("hci_pin_code_request_reply: Could not allocate memory for pbuf\n");
		return ERR_MEM;
	}

	/* Reset buffer content just to make sure */
	memset((u8_t *)p->payload, 0, HCI_PIN_CODE_REQ_REP_PLEN);

	/* Assembling command packet */
	p = hci_cmd_ass(p, HCI_PIN_CODE_REQ_REP, HCI_LINK_CTRL_OGF, HCI_PIN_CODE_REQ_REP_PLEN);
	/* Assembling cmd prameters */
	memcpy(((u8_t *)p->payload) + 4, bdaddr->addr, 6);
	((u8_t *)p->payload)[10] = pinlen;
	memcpy(((u8_t *)p->payload) + 11, pincode, pinlen);

	physbusif_output(p, p->tot_len);
	btpbuf_free(p);

	return ERR_OK;
}