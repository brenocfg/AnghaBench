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
typedef  int /*<<< orphan*/  AdvPortAddr ;
typedef  int ADV_DCNT ;

/* Variables and functions */
 int ASC_IERR_MCODE_CHKSUM ; 
 scalar_t__ AdvReadWordAutoIncLram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AdvWriteWordAutoIncLram (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  AdvWriteWordRegister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOPW_RAM_ADDR ; 

__attribute__((used)) static int AdvLoadMicrocode(AdvPortAddr iop_base, const unsigned char *buf,
			    int size, int memsize, int chksum)
{
	int i, j, end, len = 0;
	ADV_DCNT sum;

	AdvWriteWordRegister(iop_base, IOPW_RAM_ADDR, 0);

	for (i = 253 * 2; i < size; i++) {
		if (buf[i] == 0xff) {
			unsigned short word = (buf[i + 3] << 8) | buf[i + 2];
			for (j = 0; j < buf[i + 1]; j++) {
				AdvWriteWordAutoIncLram(iop_base, word);
				len += 2;
			}
			i += 3;
		} else if (buf[i] == 0xfe) {
			unsigned short word = (buf[i + 2] << 8) | buf[i + 1];
			AdvWriteWordAutoIncLram(iop_base, word);
			i += 2;
			len += 2;
		} else {
			unsigned int off = buf[i] * 2;
			unsigned short word = (buf[off + 1] << 8) | buf[off];
			AdvWriteWordAutoIncLram(iop_base, word);
			len += 2;
		}
	}

	end = len;

	while (len < memsize) {
		AdvWriteWordAutoIncLram(iop_base, 0);
		len += 2;
	}

	/* Verify the microcode checksum. */
	sum = 0;
	AdvWriteWordRegister(iop_base, IOPW_RAM_ADDR, 0);

	for (len = 0; len < end; len += 2) {
		sum += AdvReadWordAutoIncLram(iop_base);
	}

	if (sum != chksum)
		return ASC_IERR_MCODE_CHKSUM;

	return 0;
}