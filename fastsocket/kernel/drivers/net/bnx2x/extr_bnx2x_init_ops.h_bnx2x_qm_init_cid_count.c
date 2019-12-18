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
 int BP_PORT (struct bnx2x*) ; 
#define  INITOP_CLEAR 130 
#define  INITOP_INIT 129 
#define  INITOP_SET 128 
 scalar_t__ QM_INIT (int) ; 
 int /*<<< orphan*/  QM_REG_CONNNUM_0 ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_qm_init_cid_count(struct bnx2x *bp, int qm_cid_count,
				    u8 initop)
{
	int port = BP_PORT(bp);

	if (QM_INIT(qm_cid_count)) {
		switch (initop) {
		case INITOP_INIT:
			/* set in the init-value array */
		case INITOP_SET:
			REG_WR(bp, QM_REG_CONNNUM_0 + port*4,
			       qm_cid_count/16 - 1);
			break;
		case INITOP_CLEAR:
			break;
		}
	}
}