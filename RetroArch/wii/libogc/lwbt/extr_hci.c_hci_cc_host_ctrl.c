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
typedef  int u8_t ;
struct pbuf {scalar_t__ payload; } ;
struct TYPE_2__ {int flow; } ;

/* Variables and functions */
#define  HCI_READ_CUR_IACLAP 129 
#define  HCI_SET_HC_TO_H_FC 128 
 int HCI_SUCCESS ; 
 TYPE_1__* hci_dev ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

__attribute__((used)) static void hci_cc_host_ctrl(u8_t ocf,struct pbuf *p)
{
	u8_t *lap;
	u8_t i,resp_off;

	//printf("hci_cc_host_ctrl(%02x)\n",ocf);
	switch(ocf) {
		case HCI_SET_HC_TO_H_FC:
			if(((u8_t*)p->payload)[0]==HCI_SUCCESS) hci_dev->flow = 1;
			break;
		case HCI_READ_CUR_IACLAP:
			if(((u8_t*)p->payload)[0]==HCI_SUCCESS) {
				for(i=0;i<((u8_t*)p->payload)[1];i++) {
					resp_off = (i*3);
					lap = (void*)(((u8_t*)p->payload)+(2+resp_off));
					printf("lap = 00%02x%02x%02x\n",lap[2],lap[1],lap[0]);
				}
			}
			break;
	}
}