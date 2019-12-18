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
struct sg_iovec {scalar_t__ iov_base; int /*<<< orphan*/  iov_len; } ;
struct sg_io_hdr {int iovec_count; scalar_t__ dxferp; } ;

/* Variables and functions */
 int EFAULT ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 unsigned long copy_from_user (struct sg_iovec*,scalar_t__,int) ; 
 unsigned long copy_to_user (scalar_t__,void*,unsigned long) ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_trans_copy_to_user(struct sg_io_hdr *hdr, void *from,
								unsigned long n)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	unsigned long not_copied;
	int i;
	void *index = from;
	size_t remaining = n;
	size_t xfer_len;

	if (hdr->iovec_count > 0) {
		struct sg_iovec sgl;

		for (i = 0; i < hdr->iovec_count; i++) {
			not_copied = copy_from_user(&sgl, hdr->dxferp +
						i * sizeof(struct sg_iovec),
						sizeof(struct sg_iovec));
			if (not_copied)
				return -EFAULT;
			xfer_len = min(remaining, sgl.iov_len);
			not_copied = copy_to_user(sgl.iov_base, index,
								xfer_len);
			if (not_copied) {
				res = -EFAULT;
				break;
			}
			index += xfer_len;
			remaining -= xfer_len;
			if (remaining == 0)
				break;
		}
		return res;
	}
	not_copied = copy_to_user(hdr->dxferp, from, n);
	if (not_copied)
		res = -EFAULT;
	return res;
}