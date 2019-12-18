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
typedef  size_t u8 ;
typedef  int u32 ;
struct ar9170 {int dummy; } ;
typedef  enum carl9170_bw { ____Placeholder_carl9170_bw } carl9170_bw ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CARL9170_BW_20 130 
#define  CARL9170_BW_40_ABOVE 129 
#define  CARL9170_BW_40_BELOW 128 
 int ENOSYS ; 
 size_t* byte_rev_table ; 
 int /*<<< orphan*/  carl9170_regwrite (int,int) ; 
 int /*<<< orphan*/  carl9170_regwrite_begin (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_regwrite_finish () ; 
 int carl9170_regwrite_result () ; 

__attribute__((used)) static int carl9170_init_rf_bank4_pwr(struct ar9170 *ar, bool band5ghz,
				      u32 freq, enum carl9170_bw bw)
{
	int err;
	u32 d0, d1, td0, td1, fd0, fd1;
	u8 chansel;
	u8 refsel0 = 1, refsel1 = 0;
	u8 lf_synth = 0;

	switch (bw) {
	case CARL9170_BW_40_ABOVE:
		freq += 10;
		break;
	case CARL9170_BW_40_BELOW:
		freq -= 10;
		break;
	case CARL9170_BW_20:
		break;
	default:
		BUG();
		return -ENOSYS;
	}

	if (band5ghz) {
		if (freq % 10) {
			chansel = (freq - 4800) / 5;
		} else {
			chansel = ((freq - 4800) / 10) * 2;
			refsel0 = 0;
			refsel1 = 1;
		}
		chansel = byte_rev_table[chansel];
	} else {
		if (freq == 2484) {
			chansel = 10 + (freq - 2274) / 5;
			lf_synth = 1;
		} else
			chansel = 16 + (freq - 2272) / 5;
		chansel *= 4;
		chansel = byte_rev_table[chansel];
	}

	d1 =	chansel;
	d0 =	0x21 |
		refsel0 << 3 |
		refsel1 << 2 |
		lf_synth << 1;
	td0 =	d0 & 0x1f;
	td1 =	d1 & 0x1f;
	fd0 =	td1 << 5 | td0;

	td0 =	(d0 >> 5) & 0x7;
	td1 =	(d1 >> 5) & 0x7;
	fd1 =	td1 << 5 | td0;

	carl9170_regwrite_begin(ar);

	carl9170_regwrite(0x1c58b0, fd0);
	carl9170_regwrite(0x1c58e8, fd1);

	carl9170_regwrite_finish();
	err = carl9170_regwrite_result();
	if (err)
		return err;

	return 0;
}