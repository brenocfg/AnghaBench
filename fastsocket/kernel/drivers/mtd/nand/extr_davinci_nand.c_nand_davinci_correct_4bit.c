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
typedef  int u_char ;
typedef  int u32 ;
struct mtd_info {int dummy; } ;
struct davinci_nand_info {int dummy; } ;

/* Variables and functions */
 unsigned short BIT (int) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  NANDFCR_OFFSET ; 
 int /*<<< orphan*/  NANDFSR_OFFSET ; 
 int /*<<< orphan*/  NAND_4BIT_ECC_LOAD_OFFSET ; 
 int /*<<< orphan*/  NAND_ERR_ADD1_OFFSET ; 
 int /*<<< orphan*/  NAND_ERR_ADD2_OFFSET ; 
 int /*<<< orphan*/  NAND_ERR_ERRVAL1_OFFSET ; 
 int /*<<< orphan*/  NAND_ERR_ERRVAL2_OFFSET ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned short davinci_nand_readl (struct davinci_nand_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  davinci_nand_writel (struct davinci_nand_info*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  nand_davinci_readecc_4bit (struct davinci_nand_info*,int*) ; 
 struct davinci_nand_info* to_davinci_nand (struct mtd_info*) ; 

__attribute__((used)) static int nand_davinci_correct_4bit(struct mtd_info *mtd,
		u_char *data, u_char *ecc_code, u_char *null)
{
	int i;
	struct davinci_nand_info *info = to_davinci_nand(mtd);
	unsigned short ecc10[8];
	unsigned short *ecc16;
	u32 syndrome[4];
	unsigned num_errors, corrected;

	/* All bytes 0xff?  It's an erased page; ignore its ECC. */
	for (i = 0; i < 10; i++) {
		if (ecc_code[i] != 0xff)
			goto compare;
	}
	return 0;

compare:
	/* Unpack ten bytes into eight 10 bit values.  We know we're
	 * little-endian, and use type punning for less shifting/masking.
	 */
	if (WARN_ON(0x01 & (unsigned) ecc_code))
		return -EINVAL;
	ecc16 = (unsigned short *)ecc_code;

	ecc10[0] =  (ecc16[0] >>  0) & 0x3ff;
	ecc10[1] = ((ecc16[0] >> 10) & 0x3f) | ((ecc16[1] << 6) & 0x3c0);
	ecc10[2] =  (ecc16[1] >>  4) & 0x3ff;
	ecc10[3] = ((ecc16[1] >> 14) & 0x3)  | ((ecc16[2] << 2) & 0x3fc);
	ecc10[4] =  (ecc16[2] >>  8)         | ((ecc16[3] << 8) & 0x300);
	ecc10[5] =  (ecc16[3] >>  2) & 0x3ff;
	ecc10[6] = ((ecc16[3] >> 12) & 0xf)  | ((ecc16[4] << 4) & 0x3f0);
	ecc10[7] =  (ecc16[4] >>  6) & 0x3ff;

	/* Tell ECC controller about the expected ECC codes. */
	for (i = 7; i >= 0; i--)
		davinci_nand_writel(info, NAND_4BIT_ECC_LOAD_OFFSET, ecc10[i]);

	/* Allow time for syndrome calculation ... then read it.
	 * A syndrome of all zeroes 0 means no detected errors.
	 */
	davinci_nand_readl(info, NANDFSR_OFFSET);
	nand_davinci_readecc_4bit(info, syndrome);
	if (!(syndrome[0] | syndrome[1] | syndrome[2] | syndrome[3]))
		return 0;

	/*
	 * Clear any previous address calculation by doing a dummy read of an
	 * error address register.
	 */
	davinci_nand_readl(info, NAND_ERR_ADD1_OFFSET);

	/* Start address calculation, and wait for it to complete.
	 * We _could_ start reading more data while this is working,
	 * to speed up the overall page read.
	 */
	davinci_nand_writel(info, NANDFCR_OFFSET,
			davinci_nand_readl(info, NANDFCR_OFFSET) | BIT(13));
	for (;;) {
		u32	fsr = davinci_nand_readl(info, NANDFSR_OFFSET);

		switch ((fsr >> 8) & 0x0f) {
		case 0:		/* no error, should not happen */
			davinci_nand_readl(info, NAND_ERR_ERRVAL1_OFFSET);
			return 0;
		case 1:		/* five or more errors detected */
			davinci_nand_readl(info, NAND_ERR_ERRVAL1_OFFSET);
			return -EIO;
		case 2:		/* error addresses computed */
		case 3:
			num_errors = 1 + ((fsr >> 16) & 0x03);
			goto correct;
		default:	/* still working on it */
			cpu_relax();
			continue;
		}
	}

correct:
	/* correct each error */
	for (i = 0, corrected = 0; i < num_errors; i++) {
		int error_address, error_value;

		if (i > 1) {
			error_address = davinci_nand_readl(info,
						NAND_ERR_ADD2_OFFSET);
			error_value = davinci_nand_readl(info,
						NAND_ERR_ERRVAL2_OFFSET);
		} else {
			error_address = davinci_nand_readl(info,
						NAND_ERR_ADD1_OFFSET);
			error_value = davinci_nand_readl(info,
						NAND_ERR_ERRVAL1_OFFSET);
		}

		if (i & 1) {
			error_address >>= 16;
			error_value >>= 16;
		}
		error_address &= 0x3ff;
		error_address = (512 + 7) - error_address;

		if (error_address < 512) {
			data[error_address] ^= error_value;
			corrected++;
		}
	}

	return corrected;
}