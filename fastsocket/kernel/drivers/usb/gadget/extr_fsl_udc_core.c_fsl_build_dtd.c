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
typedef  int u32 ;
struct TYPE_7__ {scalar_t__ length; scalar_t__ actual; scalar_t__ dma; int /*<<< orphan*/  no_interrupt; scalar_t__ zero; } ;
struct fsl_req {TYPE_3__ req; TYPE_2__* ep; } ;
struct ep_td_struct {int size_ioc_sts; void* buff_ptr4; void* buff_ptr3; void* buff_ptr2; void* buff_ptr1; void* buff_ptr0; scalar_t__ td_dma; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  td_pool; } ;
struct TYPE_5__ {unsigned int maxpacket; } ;
struct TYPE_6__ {TYPE_1__ ep; } ;

/* Variables and functions */
 int DTD_IOC ; 
 unsigned int DTD_LENGTH_BIT_POS ; 
 int DTD_RESERVED_FIELDS ; 
 unsigned int DTD_STATUS_ACTIVE ; 
 scalar_t__ EP_MAX_LENGTH_TRANSFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VDBG (char*,...) ; 
 void* cpu_to_le32 (int) ; 
 struct ep_td_struct* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mb () ; 
 unsigned int min (scalar_t__,unsigned int) ; 
 TYPE_4__* udc_controller ; 

__attribute__((used)) static struct ep_td_struct *fsl_build_dtd(struct fsl_req *req, unsigned *length,
		dma_addr_t *dma, int *is_last)
{
	u32 swap_temp;
	struct ep_td_struct *dtd;

	/* how big will this transfer be? */
	*length = min(req->req.length - req->req.actual,
			(unsigned)EP_MAX_LENGTH_TRANSFER);

	dtd = dma_pool_alloc(udc_controller->td_pool, GFP_KERNEL, dma);
	if (dtd == NULL)
		return dtd;

	dtd->td_dma = *dma;
	/* Clear reserved field */
	swap_temp = cpu_to_le32(dtd->size_ioc_sts);
	swap_temp &= ~DTD_RESERVED_FIELDS;
	dtd->size_ioc_sts = cpu_to_le32(swap_temp);

	/* Init all of buffer page pointers */
	swap_temp = (u32) (req->req.dma + req->req.actual);
	dtd->buff_ptr0 = cpu_to_le32(swap_temp);
	dtd->buff_ptr1 = cpu_to_le32(swap_temp + 0x1000);
	dtd->buff_ptr2 = cpu_to_le32(swap_temp + 0x2000);
	dtd->buff_ptr3 = cpu_to_le32(swap_temp + 0x3000);
	dtd->buff_ptr4 = cpu_to_le32(swap_temp + 0x4000);

	req->req.actual += *length;

	/* zlp is needed if req->req.zero is set */
	if (req->req.zero) {
		if (*length == 0 || (*length % req->ep->ep.maxpacket) != 0)
			*is_last = 1;
		else
			*is_last = 0;
	} else if (req->req.length == req->req.actual)
		*is_last = 1;
	else
		*is_last = 0;

	if ((*is_last) == 0)
		VDBG("multi-dtd request!");
	/* Fill in the transfer size; set active bit */
	swap_temp = ((*length << DTD_LENGTH_BIT_POS) | DTD_STATUS_ACTIVE);

	/* Enable interrupt for the last dtd of a request */
	if (*is_last && !req->req.no_interrupt)
		swap_temp |= DTD_IOC;

	dtd->size_ioc_sts = cpu_to_le32(swap_temp);

	mb();

	VDBG("length = %d address= 0x%x", *length, (int)*dma);

	return dtd;
}