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

/* Variables and functions */
 int /*<<< orphan*/  KM_BIO_DST_IRQ ; 
 int /*<<< orphan*/  KM_BIO_SRC_IRQ ; 
 unsigned char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 

__attribute__((used)) static void tifm_sd_copy_page(struct page *dst, unsigned int dst_off,
			      struct page *src, unsigned int src_off,
			      unsigned int count)
{
	unsigned char *src_buf = kmap_atomic(src, KM_BIO_SRC_IRQ) + src_off;
	unsigned char *dst_buf = kmap_atomic(dst, KM_BIO_DST_IRQ) + dst_off;

	memcpy(dst_buf, src_buf, count);

	kunmap_atomic(dst_buf - dst_off, KM_BIO_DST_IRQ);
	kunmap_atomic(src_buf - src_off, KM_BIO_SRC_IRQ);
}