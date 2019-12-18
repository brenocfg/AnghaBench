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
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
struct ecryptfs_crypt_stat {int dummy; } ;

/* Variables and functions */
 int encrypt_scatterlist (struct ecryptfs_crypt_stat*,struct scatterlist*,struct scatterlist*,int,unsigned char*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int,int) ; 

__attribute__((used)) static int
ecryptfs_encrypt_page_offset(struct ecryptfs_crypt_stat *crypt_stat,
			     struct page *dst_page, int dst_offset,
			     struct page *src_page, int src_offset, int size,
			     unsigned char *iv)
{
	struct scatterlist src_sg, dst_sg;

	sg_init_table(&src_sg, 1);
	sg_init_table(&dst_sg, 1);

	sg_set_page(&src_sg, src_page, size, src_offset);
	sg_set_page(&dst_sg, dst_page, size, dst_offset);
	return encrypt_scatterlist(crypt_stat, &dst_sg, &src_sg, size, iv);
}