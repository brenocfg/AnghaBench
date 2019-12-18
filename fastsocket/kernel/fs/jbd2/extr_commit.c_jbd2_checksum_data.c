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
struct page {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; struct page* b_page; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  crc32_be (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*,int /*<<< orphan*/ ) ; 
 int offset_in_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u32 jbd2_checksum_data(__u32 crc32_sum, struct buffer_head *bh)
{
	struct page *page = bh->b_page;
	char *addr;
	__u32 checksum;

	addr = kmap_atomic(page, KM_USER0);
	checksum = crc32_be(crc32_sum,
		(void *)(addr + offset_in_page(bh->b_data)), bh->b_size);
	kunmap_atomic(addr, KM_USER0);

	return checksum;
}