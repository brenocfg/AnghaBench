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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct usbtxbuf {int /*<<< orphan*/ * rpData; } ;
struct pbuf {scalar_t__ len; int /*<<< orphan*/  payload; struct pbuf* next; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {int openstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  PBUF_POOL ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 size_t STACKSIZE ; 
 int /*<<< orphan*/  SYS_SwitchFiber (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ __issue_bulkread () ; 
 int /*<<< orphan*/ * __ppc_btstack2 ; 
 TYPE_1__ __usbdev ; 
 int /*<<< orphan*/  aclbufs ; 
 int /*<<< orphan*/  btmemb_free (int /*<<< orphan*/ *,struct usbtxbuf*) ; 
 struct pbuf* btpbuf_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btpbuf_free (struct pbuf*) ; 
 scalar_t__ hci_acldata_handler ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static s32 __readbulkdataCB(s32 result,void *usrdata)
{
	u8 *ptr;
	u32 len;
	struct pbuf *p,*q;
	struct usbtxbuf *buf = (struct usbtxbuf*)usrdata;

	if(__usbdev.openstate!=0x0002) return 0;

	if(result>0) {
		len = result;
		p = btpbuf_alloc(PBUF_RAW,len,PBUF_POOL);
		if(p!=NULL) {
			ptr = buf->rpData;
			for(q=p;q!=NULL && len>0;q=q->next) {
				memcpy(q->payload,ptr,q->len);
				ptr += q->len;
				len -= q->len;
			}

			SYS_SwitchFiber((u32)p,0,0,0,(u32)hci_acldata_handler,(u32)(&__ppc_btstack2[STACKSIZE]));
			btpbuf_free(p);
		} else
			ERROR("__readbulkdataCB: Could not allocate memory for pbuf.\n");
	}
	btmemb_free(&aclbufs,buf);

	return __issue_bulkread();
}