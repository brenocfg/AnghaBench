#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  scalar_t__ u_long ;
struct xfer_info_t {int /*<<< orphan*/  EraseCount; int /*<<< orphan*/  Offset; int /*<<< orphan*/  state; } ;
struct erase_info {int len; scalar_t__ priv; int /*<<< orphan*/  addr; int /*<<< orphan*/  callback; TYPE_4__* mtd; } ;
struct TYPE_7__ {TYPE_4__* mtd; } ;
struct TYPE_6__ {int EraseUnitSize; } ;
struct TYPE_8__ {TYPE_2__ mbd; TYPE_1__ header; struct xfer_info_t* XferInfo; } ;
typedef  TYPE_3__ partition_t ;
struct TYPE_9__ {int (* erase ) (TYPE_4__*,struct erase_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  XFER_ERASING ; 
 int /*<<< orphan*/  ftl_erase_callback ; 
 int /*<<< orphan*/  kfree (struct erase_info*) ; 
 struct erase_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_4__*,struct erase_info*) ; 

__attribute__((used)) static int erase_xfer(partition_t *part,
		      uint16_t xfernum)
{
    int ret;
    struct xfer_info_t *xfer;
    struct erase_info *erase;

    xfer = &part->XferInfo[xfernum];
    DEBUG(1, "ftl_cs: erasing xfer unit at 0x%x\n", xfer->Offset);
    xfer->state = XFER_ERASING;

    /* Is there a free erase slot? Always in MTD. */


    erase=kmalloc(sizeof(struct erase_info), GFP_KERNEL);
    if (!erase)
            return -ENOMEM;

    erase->mtd = part->mbd.mtd;
    erase->callback = ftl_erase_callback;
    erase->addr = xfer->Offset;
    erase->len = 1 << part->header.EraseUnitSize;
    erase->priv = (u_long)part;

    ret = part->mbd.mtd->erase(part->mbd.mtd, erase);

    if (!ret)
	    xfer->EraseCount++;
    else
	    kfree(erase);

    return ret;
}