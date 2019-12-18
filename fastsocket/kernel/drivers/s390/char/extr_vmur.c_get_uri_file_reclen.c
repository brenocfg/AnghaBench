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
struct urdev {int dummy; } ;
struct file_control_block {int file_stat; int rec_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FLG_CP_DUMP ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int diag_read_next_file_info (struct file_control_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct file_control_block*) ; 
 struct file_control_block* kmalloc (int,int) ; 

__attribute__((used)) static int get_uri_file_reclen(struct urdev *urd)
{
	struct file_control_block *fcb;
	int rc;

	fcb = kmalloc(sizeof(*fcb), GFP_KERNEL | GFP_DMA);
	if (!fcb)
		return -ENOMEM;
	rc = diag_read_next_file_info(fcb, 0);
	if (rc)
		goto fail_free;
	if (fcb->file_stat & FLG_CP_DUMP)
		rc = 0;
	else
		rc = fcb->rec_len;

fail_free:
	kfree(fcb);
	return rc;
}