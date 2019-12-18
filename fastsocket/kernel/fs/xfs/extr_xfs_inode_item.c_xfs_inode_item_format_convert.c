#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int i_len; TYPE_7__* i_addr; } ;
typedef  TYPE_5__ xfs_log_iovec_t ;
struct TYPE_11__ {int /*<<< orphan*/  __u_bits; } ;
struct TYPE_12__ {TYPE_1__ ilfu_uuid; } ;
struct TYPE_16__ {int /*<<< orphan*/  ilf_boffset; int /*<<< orphan*/  ilf_len; int /*<<< orphan*/  ilf_blkno; TYPE_2__ ilf_u; int /*<<< orphan*/  ilf_ino; int /*<<< orphan*/  ilf_dsize; int /*<<< orphan*/  ilf_asize; int /*<<< orphan*/  ilf_fields; int /*<<< orphan*/  ilf_size; int /*<<< orphan*/  ilf_type; } ;
typedef  TYPE_6__ xfs_inode_log_format_t ;
struct TYPE_13__ {int /*<<< orphan*/  __u_bits; } ;
struct TYPE_14__ {TYPE_3__ ilfu_uuid; } ;
struct TYPE_17__ {int /*<<< orphan*/  ilf_boffset; int /*<<< orphan*/  ilf_len; int /*<<< orphan*/  ilf_blkno; TYPE_4__ ilf_u; int /*<<< orphan*/  ilf_ino; int /*<<< orphan*/  ilf_dsize; int /*<<< orphan*/  ilf_asize; int /*<<< orphan*/  ilf_fields; int /*<<< orphan*/  ilf_size; int /*<<< orphan*/  ilf_type; } ;
typedef  TYPE_7__ xfs_inode_log_format_64_t ;
typedef  TYPE_7__ xfs_inode_log_format_32_t ;
typedef  int /*<<< orphan*/  uuid_t ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
xfs_inode_item_format_convert(
	xfs_log_iovec_t		*buf,
	xfs_inode_log_format_t	*in_f)
{
	if (buf->i_len == sizeof(xfs_inode_log_format_32_t)) {
		xfs_inode_log_format_32_t *in_f32 = buf->i_addr;

		in_f->ilf_type = in_f32->ilf_type;
		in_f->ilf_size = in_f32->ilf_size;
		in_f->ilf_fields = in_f32->ilf_fields;
		in_f->ilf_asize = in_f32->ilf_asize;
		in_f->ilf_dsize = in_f32->ilf_dsize;
		in_f->ilf_ino = in_f32->ilf_ino;
		/* copy biggest field of ilf_u */
		memcpy(in_f->ilf_u.ilfu_uuid.__u_bits,
		       in_f32->ilf_u.ilfu_uuid.__u_bits,
		       sizeof(uuid_t));
		in_f->ilf_blkno = in_f32->ilf_blkno;
		in_f->ilf_len = in_f32->ilf_len;
		in_f->ilf_boffset = in_f32->ilf_boffset;
		return 0;
	} else if (buf->i_len == sizeof(xfs_inode_log_format_64_t)){
		xfs_inode_log_format_64_t *in_f64 = buf->i_addr;

		in_f->ilf_type = in_f64->ilf_type;
		in_f->ilf_size = in_f64->ilf_size;
		in_f->ilf_fields = in_f64->ilf_fields;
		in_f->ilf_asize = in_f64->ilf_asize;
		in_f->ilf_dsize = in_f64->ilf_dsize;
		in_f->ilf_ino = in_f64->ilf_ino;
		/* copy biggest field of ilf_u */
		memcpy(in_f->ilf_u.ilfu_uuid.__u_bits,
		       in_f64->ilf_u.ilfu_uuid.__u_bits,
		       sizeof(uuid_t));
		in_f->ilf_blkno = in_f64->ilf_blkno;
		in_f->ilf_len = in_f64->ilf_len;
		in_f->ilf_boffset = in_f64->ilf_boffset;
		return 0;
	}
	return EFSCORRUPTED;
}