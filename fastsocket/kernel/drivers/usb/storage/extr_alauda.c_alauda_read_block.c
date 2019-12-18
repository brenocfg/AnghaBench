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
typedef  int /*<<< orphan*/  u16 ;
struct us_data {int dummy; } ;
struct TYPE_2__ {unsigned int pagesize; } ;

/* Variables and functions */
 TYPE_1__ MEDIA_INFO (struct us_data*) ; 
 int USB_STOR_XFER_GOOD ; 
 int alauda_read_block_raw (struct us_data*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,unsigned int) ; 

__attribute__((used)) static int alauda_read_block(struct us_data *us, u16 pba,
		unsigned int page, unsigned int pages, unsigned char *data)
{
	int i, rc;
	unsigned int pagesize = MEDIA_INFO(us).pagesize;

	rc = alauda_read_block_raw(us, pba, page, pages, data);
	if (rc != USB_STOR_XFER_GOOD)
		return rc;

	/* Cut out the redundancy data */
	for (i = 0; i < pages; i++) {
		int dest_offset = i * pagesize;
		int src_offset = i * (pagesize + 64);
		memmove(data + dest_offset, data + src_offset, pagesize);
	}

	return rc;
}