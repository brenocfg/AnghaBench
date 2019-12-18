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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pbuf {scalar_t__ payload; } ;
struct bte_pcb {scalar_t__ state; int /*<<< orphan*/  data_pcb; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  ERR_CLSD ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_VAL ; 
 int HIDP_DATA_RTYPE_OUPUT ; 
 int HIDP_TRANS_DATA ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 scalar_t__ STATE_DISCONNECTED ; 
 scalar_t__ STATE_DISCONNECTING ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  l2ca_datawrite (int /*<<< orphan*/ ,struct pbuf*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int /*<<< orphan*/ ) ; 

s32 bte_senddata(struct bte_pcb *pcb,void *message,u16 len)
{
	err_t err;
	struct pbuf *p;

	if(pcb==NULL || message==NULL || len==0) return ERR_VAL;
	if(pcb->state==STATE_DISCONNECTING || pcb->state==STATE_DISCONNECTED) return ERR_CLSD;

	if((p=btpbuf_alloc(PBUF_RAW,(1 + len),PBUF_RAM))==NULL) {
		ERROR("bte_senddata: Could not allocate memory for pbuf\n");
		return ERR_MEM;
	}

	((u8*)p->payload)[0] = (HIDP_TRANS_DATA|HIDP_DATA_RTYPE_OUPUT);
	memcpy(p->payload+1,message,len);

	err = l2ca_datawrite(pcb->data_pcb,p);
	btpbuf_free(p);

	return err;
}