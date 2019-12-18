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
struct rx_ring_info {int rbr_block_size; int* rbr_sizes; } ;

/* Variables and functions */
 int EINVAL ; 
 int RBR_BLKSIZE_16K ; 
 int RBR_BLKSIZE_32K ; 
 int RBR_BLKSIZE_4K ; 
 int RBR_BLKSIZE_8K ; 
 int RBR_BUFSZ0_1K ; 
 int RBR_BUFSZ0_256 ; 
 int RBR_BUFSZ0_2K ; 
 int RBR_BUFSZ0_512 ; 
 int RBR_BUFSZ1_1K ; 
 int RBR_BUFSZ1_2K ; 
 int RBR_BUFSZ1_4K ; 
 int RBR_BUFSZ1_8K ; 
 int RBR_BUFSZ2_16K ; 
 int RBR_BUFSZ2_2K ; 
 int RBR_BUFSZ2_4K ; 
 int RBR_BUFSZ2_8K ; 
 int RBR_CFIG_B_BLKSIZE_SHIFT ; 
 int RBR_CFIG_B_BUFSZ0_SHIFT ; 
 int RBR_CFIG_B_BUFSZ1_SHIFT ; 
 int RBR_CFIG_B_BUFSZ2_SHIFT ; 
 int RBR_CFIG_B_VLD0 ; 
 int RBR_CFIG_B_VLD1 ; 
 int RBR_CFIG_B_VLD2 ; 

__attribute__((used)) static int niu_compute_rbr_cfig_b(struct rx_ring_info *rp, u64 *ret)
{
	u64 val = 0;

	*ret = 0;
	switch (rp->rbr_block_size) {
	case 4 * 1024:
		val |= (RBR_BLKSIZE_4K << RBR_CFIG_B_BLKSIZE_SHIFT);
		break;
	case 8 * 1024:
		val |= (RBR_BLKSIZE_8K << RBR_CFIG_B_BLKSIZE_SHIFT);
		break;
	case 16 * 1024:
		val |= (RBR_BLKSIZE_16K << RBR_CFIG_B_BLKSIZE_SHIFT);
		break;
	case 32 * 1024:
		val |= (RBR_BLKSIZE_32K << RBR_CFIG_B_BLKSIZE_SHIFT);
		break;
	default:
		return -EINVAL;
	}
	val |= RBR_CFIG_B_VLD2;
	switch (rp->rbr_sizes[2]) {
	case 2 * 1024:
		val |= (RBR_BUFSZ2_2K << RBR_CFIG_B_BUFSZ2_SHIFT);
		break;
	case 4 * 1024:
		val |= (RBR_BUFSZ2_4K << RBR_CFIG_B_BUFSZ2_SHIFT);
		break;
	case 8 * 1024:
		val |= (RBR_BUFSZ2_8K << RBR_CFIG_B_BUFSZ2_SHIFT);
		break;
	case 16 * 1024:
		val |= (RBR_BUFSZ2_16K << RBR_CFIG_B_BUFSZ2_SHIFT);
		break;

	default:
		return -EINVAL;
	}
	val |= RBR_CFIG_B_VLD1;
	switch (rp->rbr_sizes[1]) {
	case 1 * 1024:
		val |= (RBR_BUFSZ1_1K << RBR_CFIG_B_BUFSZ1_SHIFT);
		break;
	case 2 * 1024:
		val |= (RBR_BUFSZ1_2K << RBR_CFIG_B_BUFSZ1_SHIFT);
		break;
	case 4 * 1024:
		val |= (RBR_BUFSZ1_4K << RBR_CFIG_B_BUFSZ1_SHIFT);
		break;
	case 8 * 1024:
		val |= (RBR_BUFSZ1_8K << RBR_CFIG_B_BUFSZ1_SHIFT);
		break;

	default:
		return -EINVAL;
	}
	val |= RBR_CFIG_B_VLD0;
	switch (rp->rbr_sizes[0]) {
	case 256:
		val |= (RBR_BUFSZ0_256 << RBR_CFIG_B_BUFSZ0_SHIFT);
		break;
	case 512:
		val |= (RBR_BUFSZ0_512 << RBR_CFIG_B_BUFSZ0_SHIFT);
		break;
	case 1 * 1024:
		val |= (RBR_BUFSZ0_1K << RBR_CFIG_B_BUFSZ0_SHIFT);
		break;
	case 2 * 1024:
		val |= (RBR_BUFSZ0_2K << RBR_CFIG_B_BUFSZ0_SHIFT);
		break;

	default:
		return -EINVAL;
	}

	*ret = val;
	return 0;
}