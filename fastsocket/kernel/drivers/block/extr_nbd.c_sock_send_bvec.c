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
struct nbd_device {int dummy; } ;
struct bio_vec {int bv_offset; int /*<<< orphan*/  bv_page; int /*<<< orphan*/  bv_len; } ;

/* Variables and functions */
 void* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int sock_xmit (struct nbd_device*,int,void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int sock_send_bvec(struct nbd_device *lo, struct bio_vec *bvec,
		int flags)
{
	int result;
	void *kaddr = kmap(bvec->bv_page);
	result = sock_xmit(lo, 1, kaddr + bvec->bv_offset, bvec->bv_len, flags);
	kunmap(bvec->bv_page);
	return result;
}