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
typedef  int u64 ;
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int BISTEN_LSB ; 
 int R_OPCODE_LSB ; 
 int R_OP_SHIFT ; 
 int R_TDI_LSB ; 
 int SJA_EN ; 
 int /*<<< orphan*/  kr_r_access ; 
 int /*<<< orphan*/  kr_scratch ; 
 int qib_r_wait_for_rdy (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_read_kreg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qib_r_shift(struct qib_devdata *dd, int bisten,
		       int len, u8 *inp, u8 *outp)
{
	u64 valbase, val;
	int ret, pos;

	valbase = SJA_EN | (bisten << BISTEN_LSB) |
		(R_OP_SHIFT << R_OPCODE_LSB);
	ret = qib_r_wait_for_rdy(dd);
	if (ret < 0)
		goto bail;
	for (pos = 0; pos < len; ++pos) {
		val = valbase;
		if (outp) {
			outp[pos >> 3] &= ~(1 << (pos & 7));
			outp[pos >> 3] |= (ret << (pos & 7));
		}
		if (inp) {
			int tdi = inp[pos >> 3] >> (pos & 7);
			val |= ((tdi & 1) << R_TDI_LSB);
		}
		qib_write_kreg(dd, kr_r_access, val);
		qib_read_kreg32(dd, kr_scratch);
		ret = qib_r_wait_for_rdy(dd);
		if (ret < 0)
			break;
	}
	/* Restore to NOP between operations. */
	val =  SJA_EN | (bisten << BISTEN_LSB);
	qib_write_kreg(dd, kr_r_access, val);
	qib_read_kreg32(dd, kr_scratch);
	ret = qib_r_wait_for_rdy(dd);

	if (ret >= 0)
		ret = pos;
bail:
	return ret;
}