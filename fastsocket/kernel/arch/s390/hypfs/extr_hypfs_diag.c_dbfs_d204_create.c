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
struct dbfs_d204_hdr {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  sc; int /*<<< orphan*/  version; } ;
struct dbfs_d204 {TYPE_1__ hdr; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBFS_D204_HDR_VERSION ; 
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int diag204_buf_pages ; 
 int diag204_do_store (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  diag204_store_sc ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 struct dbfs_d204* page_align_ptr (void*) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (int) ; 

__attribute__((used)) static int dbfs_d204_create(void **data, void **data_free_ptr, size_t *size)
{
	struct dbfs_d204 *d204;
	int rc, buf_size;
	void *base;

	buf_size = PAGE_SIZE * (diag204_buf_pages + 1) + sizeof(d204->hdr);
	base = vmalloc(buf_size);
	if (!base)
		return -ENOMEM;
	memset(base, 0, buf_size);
	d204 = page_align_ptr(base + sizeof(d204->hdr)) - sizeof(d204->hdr);
	rc = diag204_do_store(d204->buf, diag204_buf_pages);
	if (rc) {
		vfree(base);
		return rc;
	}
	d204->hdr.version = DBFS_D204_HDR_VERSION;
	d204->hdr.len = PAGE_SIZE * diag204_buf_pages;
	d204->hdr.sc = diag204_store_sc;
	*data = d204;
	*data_free_ptr = base;
	*size = d204->hdr.len + sizeof(struct dbfs_d204_hdr);
	return 0;
}