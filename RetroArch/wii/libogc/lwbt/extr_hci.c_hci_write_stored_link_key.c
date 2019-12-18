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
 int /*<<< orphan*/  HCI_HC_BB_OGF ; 
 int /*<<< orphan*/  HCI_WRITE_STORED_LINK_KEY ; 
 int /*<<< orphan*/  HCI_WRITE_STORED_LINK_KEY_PLEN ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 struct pbuf* hci_cmd_ass (struct pbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  physbusif_output (struct pbuf*,int /*<<< orphan*/ ) ; 

err_t hci_write_stored_link_key(struct bd_addr *bdaddr, u8_t *link)
{
  struct pbuf *p;

	if((p = btpbuf_alloc(PBUF_RAW, HCI_WRITE_STORED_LINK_KEY_PLEN, PBUF_RAM)) == NULL) {
		ERROR("hci_write_stored_link_key: Could not allocate memory for pbuf\n");
		return ERR_MEM;
	}
	/* Assembling command packet */
	p = hci_cmd_ass(p, HCI_WRITE_STORED_LINK_KEY, HCI_HC_BB_OGF, HCI_WRITE_STORED_LINK_KEY_PLEN);
	/* Assembling cmd prameters */
	((u8_t *)p->payload)[4] = 0x01;
	memcpy(((u8_t *)p->payload) + 5, bdaddr->addr, 6);
	memcpy(((u8_t *)p->payload) + 11, link, 16);

	physbusif_output(p, p->tot_len);
	btpbuf_free(p);

	return ERR_OK;
}