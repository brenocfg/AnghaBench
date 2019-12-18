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
typedef  int u8 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E1H (struct bnx2x*) ; 
#define  INITOP_CLEAR 130 
#define  INITOP_INIT 129 
#define  INITOP_SET 128 
 int /*<<< orphan*/  QM_INIT (int) ; 
 int /*<<< orphan*/  QM_REG_BASEADDR ; 
 int /*<<< orphan*/  QM_REG_BASEADDR_EXT_A ; 
 int /*<<< orphan*/  QM_REG_PTRTBL ; 
 int /*<<< orphan*/  QM_REG_PTRTBL_EXT_A ; 
 int /*<<< orphan*/  bnx2x_qm_set_ptr_table (struct bnx2x*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_qm_init_ptr_table(struct bnx2x *bp, int qm_cid_count,
				    u8 initop)
{
	if (!QM_INIT(qm_cid_count))
		return;

	switch (initop) {
	case INITOP_INIT:
		/* set in the init-value array */
	case INITOP_SET:
		bnx2x_qm_set_ptr_table(bp, qm_cid_count,
				       QM_REG_BASEADDR, QM_REG_PTRTBL);
		if (CHIP_IS_E1H(bp))
			bnx2x_qm_set_ptr_table(bp, qm_cid_count,
					       QM_REG_BASEADDR_EXT_A,
					       QM_REG_PTRTBL_EXT_A);
		break;
	case INITOP_CLEAR:
		break;
	}
}