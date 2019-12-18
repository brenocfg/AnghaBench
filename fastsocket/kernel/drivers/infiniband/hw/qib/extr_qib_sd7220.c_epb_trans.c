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
typedef  int /*<<< orphan*/  u16 ;
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int EPB_TRANS_ERR ; 
 int EPB_TRANS_RDY ; 
 int EPB_TRANS_TRIES ; 
 int qib_read_kreg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int qib_read_kreg64 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int epb_trans(struct qib_devdata *dd, u16 reg, u64 i_val, u64 *o_vp)
{
	int tries;
	u64 transval;

	qib_write_kreg(dd, reg, i_val);
	/* Throw away first read, as RDY bit may be stale */
	transval = qib_read_kreg64(dd, reg);

	for (tries = EPB_TRANS_TRIES; tries; --tries) {
		transval = qib_read_kreg32(dd, reg);
		if (transval & EPB_TRANS_RDY)
			break;
		udelay(5);
	}
	if (transval & EPB_TRANS_ERR)
		return -1;
	if (tries > 0 && o_vp)
		*o_vp = transval;
	return tries;
}