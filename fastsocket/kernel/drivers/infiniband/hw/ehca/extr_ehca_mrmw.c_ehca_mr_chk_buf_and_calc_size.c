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
typedef  int u64 ;
typedef  int u32 ;
struct ib_phys_buf {int addr; int size; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  ehca_gen_err (char*,...) ; 

int ehca_mr_chk_buf_and_calc_size(struct ib_phys_buf *phys_buf_array,
				  int num_phys_buf,
				  u64 *iova_start,
				  u64 *size)
{
	struct ib_phys_buf *pbuf = phys_buf_array;
	u64 size_count = 0;
	u32 i;

	if (num_phys_buf == 0) {
		ehca_gen_err("bad phys buf array len, num_phys_buf=0");
		return -EINVAL;
	}
	/* check first buffer */
	if (((u64)iova_start & ~PAGE_MASK) != (pbuf->addr & ~PAGE_MASK)) {
		ehca_gen_err("iova_start/addr mismatch, iova_start=%p "
			     "pbuf->addr=%llx pbuf->size=%llx",
			     iova_start, pbuf->addr, pbuf->size);
		return -EINVAL;
	}
	if (((pbuf->addr + pbuf->size) % PAGE_SIZE) &&
	    (num_phys_buf > 1)) {
		ehca_gen_err("addr/size mismatch in 1st buf, pbuf->addr=%llx "
			     "pbuf->size=%llx", pbuf->addr, pbuf->size);
		return -EINVAL;
	}

	for (i = 0; i < num_phys_buf; i++) {
		if ((i > 0) && (pbuf->addr % PAGE_SIZE)) {
			ehca_gen_err("bad address, i=%x pbuf->addr=%llx "
				     "pbuf->size=%llx",
				     i, pbuf->addr, pbuf->size);
			return -EINVAL;
		}
		if (((i > 0) &&	/* not 1st */
		     (i < (num_phys_buf - 1)) &&	/* not last */
		     (pbuf->size % PAGE_SIZE)) || (pbuf->size == 0)) {
			ehca_gen_err("bad size, i=%x pbuf->size=%llx",
				     i, pbuf->size);
			return -EINVAL;
		}
		size_count += pbuf->size;
		pbuf++;
	}

	*size = size_count;
	return 0;
}