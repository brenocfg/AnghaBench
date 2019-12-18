#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_3__ {int msg_id; } ;
struct bfi_mbmsg {TYPE_1__ mh; } ;
struct bfi_flash_write_rsp {size_t status; } ;
struct bfi_flash_read_rsp {size_t status; size_t length; } ;
struct bfi_flash_query_rsp {size_t status; } ;
struct bfa_flash_attr {size_t status; size_t npart; TYPE_2__* part; } ;
struct bfa_flash {size_t ubuf; size_t status; size_t residue; size_t offset; scalar_t__ dbuf_kva; int /*<<< orphan*/  op_busy; } ;
struct TYPE_4__ {size_t part_type; size_t part_instance; size_t part_off; size_t part_size; size_t part_len; size_t part_status; } ;

/* Variables and functions */
 size_t BFA_STATUS_OK ; 
#define  BFI_FLASH_I2H_BOOT_VER_RSP 132 
#define  BFI_FLASH_I2H_EVENT 131 
#define  BFI_FLASH_I2H_QUERY_RSP 130 
#define  BFI_FLASH_I2H_READ_RSP 129 
#define  BFI_FLASH_I2H_WRITE_RSP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* be32_to_cpu (size_t) ; 
 int /*<<< orphan*/  bfa_flash_cb (struct bfa_flash*) ; 
 int /*<<< orphan*/  bfa_flash_read_send (struct bfa_flash*) ; 
 int /*<<< orphan*/  bfa_flash_write_send (struct bfa_flash*) ; 
 int /*<<< orphan*/  memcpy (size_t,scalar_t__,size_t) ; 

__attribute__((used)) static void
bfa_flash_intr(void *flasharg, struct bfi_mbmsg *msg)
{
	struct bfa_flash *flash = flasharg;
	u32	status;

	union {
		struct bfi_flash_query_rsp *query;
		struct bfi_flash_write_rsp *write;
		struct bfi_flash_read_rsp *read;
		struct bfi_mbmsg   *msg;
	} m;

	m.msg = msg;

	/* receiving response after ioc failure */
	if (!flash->op_busy && msg->mh.msg_id != BFI_FLASH_I2H_EVENT)
		return;

	switch (msg->mh.msg_id) {
	case BFI_FLASH_I2H_QUERY_RSP:
		status = be32_to_cpu(m.query->status);
		if (status == BFA_STATUS_OK) {
			u32	i;
			struct bfa_flash_attr *attr, *f;

			attr = (struct bfa_flash_attr *) flash->ubuf;
			f = (struct bfa_flash_attr *) flash->dbuf_kva;
			attr->status = be32_to_cpu(f->status);
			attr->npart = be32_to_cpu(f->npart);
			for (i = 0; i < attr->npart; i++) {
				attr->part[i].part_type =
					be32_to_cpu(f->part[i].part_type);
				attr->part[i].part_instance =
					be32_to_cpu(f->part[i].part_instance);
				attr->part[i].part_off =
					be32_to_cpu(f->part[i].part_off);
				attr->part[i].part_size =
					be32_to_cpu(f->part[i].part_size);
				attr->part[i].part_len =
					be32_to_cpu(f->part[i].part_len);
				attr->part[i].part_status =
					be32_to_cpu(f->part[i].part_status);
			}
		}
		flash->status = status;
		bfa_flash_cb(flash);
		break;
	case BFI_FLASH_I2H_WRITE_RSP:
		status = be32_to_cpu(m.write->status);
		if (status != BFA_STATUS_OK || flash->residue == 0) {
			flash->status = status;
			bfa_flash_cb(flash);
		} else
			bfa_flash_write_send(flash);
		break;
	case BFI_FLASH_I2H_READ_RSP:
		status = be32_to_cpu(m.read->status);
		if (status != BFA_STATUS_OK) {
			flash->status = status;
			bfa_flash_cb(flash);
		} else {
			u32 len = be32_to_cpu(m.read->length);
			memcpy(flash->ubuf + flash->offset,
			       flash->dbuf_kva, len);
			flash->residue -= len;
			flash->offset += len;
			if (flash->residue == 0) {
				flash->status = status;
				bfa_flash_cb(flash);
			} else
				bfa_flash_read_send(flash);
		}
		break;
	case BFI_FLASH_I2H_BOOT_VER_RSP:
	case BFI_FLASH_I2H_EVENT:
		break;
	default:
		WARN_ON(1);
	}
}