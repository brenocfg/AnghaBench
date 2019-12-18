#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct xfer_info_t {int /*<<< orphan*/  state; scalar_t__ Offset; int /*<<< orphan*/  EraseCount; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_7__ {TYPE_4__* mtd; } ;
struct TYPE_9__ {int /*<<< orphan*/  BAMOffset; void* EraseCount; int /*<<< orphan*/  LogicalEUN; } ;
struct TYPE_8__ {int BlocksPerUnit; TYPE_1__ mbd; TYPE_3__ header; struct xfer_info_t* XferInfo; } ;
typedef  TYPE_2__ partition_t ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  header ;
typedef  TYPE_3__ erase_unit_header_t ;
struct TYPE_10__ {int (* write ) (TYPE_4__*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_CONTROL ; 
 int /*<<< orphan*/  DEBUG (int,char*,scalar_t__) ; 
 int SECTOR_SIZE ; 
 int /*<<< orphan*/  XFER_FAILED ; 
 int /*<<< orphan*/  XFER_PREPARED ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_4__*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_4__*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prepare_xfer(partition_t *part, int i)
{
    erase_unit_header_t header;
    struct xfer_info_t *xfer;
    int nbam, ret;
    uint32_t ctl;
    ssize_t retlen;
    loff_t offset;

    xfer = &part->XferInfo[i];
    xfer->state = XFER_FAILED;

    DEBUG(1, "ftl_cs: preparing xfer unit at 0x%x\n", xfer->Offset);

    /* Write the transfer unit header */
    header = part->header;
    header.LogicalEUN = cpu_to_le16(0xffff);
    header.EraseCount = cpu_to_le32(xfer->EraseCount);

    ret = part->mbd.mtd->write(part->mbd.mtd, xfer->Offset, sizeof(header),
			   &retlen, (u_char *)&header);

    if (ret) {
	return ret;
    }

    /* Write the BAM stub */
    nbam = (part->BlocksPerUnit * sizeof(uint32_t) +
	    le32_to_cpu(part->header.BAMOffset) + SECTOR_SIZE - 1) / SECTOR_SIZE;

    offset = xfer->Offset + le32_to_cpu(part->header.BAMOffset);
    ctl = cpu_to_le32(BLOCK_CONTROL);

    for (i = 0; i < nbam; i++, offset += sizeof(uint32_t)) {

	ret = part->mbd.mtd->write(part->mbd.mtd, offset, sizeof(uint32_t),
			       &retlen, (u_char *)&ctl);

	if (ret)
	    return ret;
    }
    xfer->state = XFER_PREPARED;
    return 0;

}