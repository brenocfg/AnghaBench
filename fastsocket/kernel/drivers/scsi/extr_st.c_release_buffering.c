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
struct st_buffer {scalar_t__ sg_segs; scalar_t__ do_dio; } ;
struct scsi_tape {struct st_buffer* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  sgl_unmap_user_pages (struct st_buffer*,scalar_t__,int) ; 

__attribute__((used)) static void release_buffering(struct scsi_tape *STp, int is_read)
{
	struct st_buffer *STbp;

	STbp = STp->buffer;
	if (STbp->do_dio) {
		sgl_unmap_user_pages(STbp, STbp->do_dio, is_read);
		STbp->do_dio = 0;
		STbp->sg_segs = 0;
	}
}