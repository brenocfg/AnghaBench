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
typedef  scalar_t__ u32 ;
struct pbuf {int /*<<< orphan*/  tot_len; scalar_t__ payload; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  HCI_HC_BB_OGF ; 
 int /*<<< orphan*/  HCI_SET_EV_FILTER_OCF ; 
 scalar_t__ HCI_SET_EV_FILTER_PLEN ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 struct pbuf* hci_cmd_ass (struct pbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int*,scalar_t__) ; 
 int /*<<< orphan*/  physbusif_output (struct pbuf*,int /*<<< orphan*/ ) ; 

err_t hci_set_event_filter(u8_t filter_type,u8_t filter_cond_type,u8_t *cond)
{
	u32 cond_len = 0;
	struct pbuf *p = NULL;

	switch(filter_type) {
		case 0x00:
			cond_len = 0x00;
			break;
		case 0x01:
			switch(filter_cond_type) {
				case 0x00:
					cond_len = 0x00;
					break;
				case 0x01:
					cond_len = 0x06;
					break;
				case 0x02:
					cond_len = 0x06;
					break;
				default:
					break;
			}
			break;
		case 0x02:
			switch(filter_cond_type) {
				case 0x00:
					cond_len = 0x01;
					break;
				case 0x01:
					cond_len = 0x07;
					break;
				case 0x02:
					cond_len = 0x07;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	if((p=btpbuf_alloc(PBUF_RAW,HCI_SET_EV_FILTER_PLEN+cond_len,PBUF_RAM))==NULL) {
		ERROR("hci_set_event_filter: Could not allocate memory for pbuf\n");
		return ERR_MEM;
	}

	p = hci_cmd_ass(p,HCI_SET_EV_FILTER_OCF,HCI_HC_BB_OGF,HCI_SET_EV_FILTER_PLEN+cond_len);
	((u8_t*)p->payload)[4] = filter_type;
	((u8_t*)p->payload)[5] = filter_cond_type;
	if(cond_len>0) memcpy(p->payload+6,cond,cond_len);

	physbusif_output(p,p->tot_len);
	btpbuf_free(p);

	return ERR_OK;
}