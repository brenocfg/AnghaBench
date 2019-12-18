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
typedef  scalar_t__ u8_t ;
struct pbuf {int /*<<< orphan*/  tot_len; scalar_t__ payload; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 scalar_t__ HCI_W_VENDOR_CMD_PLEN ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 struct pbuf* hci_cmd_ass (struct pbuf*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,void*,scalar_t__) ; 
 int /*<<< orphan*/  physbusif_output (struct pbuf*,int /*<<< orphan*/ ) ; 

err_t hci_vendor_specific_command(u8_t ocf,u8_t ogf,void *data,u8_t len)
{
	struct pbuf *p = NULL;

	if((p=btpbuf_alloc(PBUF_RAW,HCI_W_VENDOR_CMD_PLEN + len,PBUF_RAM))==NULL) {
		ERROR("hci_vendor_specific_patch: Could not allocate memory for pbuf\n");
		return ERR_MEM;
	}

	/* Assembling command packet */
	p = hci_cmd_ass(p,ocf,ogf,HCI_W_VENDOR_CMD_PLEN + len);
	/* Assembling cmd prameters */
	memcpy(((u8_t*)p->payload + 4),data,len);

	physbusif_output(p, p->tot_len);
	btpbuf_free(p);

	return ERR_OK;
}