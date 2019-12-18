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
typedef  int /*<<< orphan*/  u16_t ;
struct bte_pcb {int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* recv ) (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  HIDP_DATA_RTYPE_FEATURE 131 
#define  HIDP_DATA_RTYPE_INPUT 130 
#define  HIDP_DATA_RTYPE_OTHER 129 
#define  HIDP_DATA_RTYPE_OUPUT 128 
 int /*<<< orphan*/  LOG (char*,struct bte_pcb*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bte_process_data(struct bte_pcb *pcb,u8_t param,void *buf,u16_t len)
{
	LOG("bte_process_data(%p)\n",pcb);
	switch(param) {
		case HIDP_DATA_RTYPE_INPUT:
			if(pcb->recv!=NULL) pcb->recv(pcb->cbarg,buf,len);
			break;
		case HIDP_DATA_RTYPE_OTHER:
		case HIDP_DATA_RTYPE_OUPUT:
		case HIDP_DATA_RTYPE_FEATURE:
			break;
		default:
			break;
	}
}