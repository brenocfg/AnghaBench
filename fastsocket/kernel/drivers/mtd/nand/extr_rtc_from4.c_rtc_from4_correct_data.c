#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct mtd_info {int dummy; } ;
struct TYPE_4__ {int* index_of; int nn; int* alpha_to; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL0 ; 
 scalar_t__ RTC_FROM4_RS_ECC ; 
 scalar_t__ RTC_FROM4_RS_ECC_CHK ; 
 unsigned short RTC_FROM4_RS_ECC_CHK_ERROR ; 
 scalar_t__ bitrev8 (unsigned short volatile) ; 
 int decode_rs8 (TYPE_1__*,scalar_t__*,int*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* rs_decoder ; 
 size_t rs_modnn (TYPE_1__*,int) ; 
 scalar_t__ rtc_from4_fio_base ; 

__attribute__((used)) static int rtc_from4_correct_data(struct mtd_info *mtd, const u_char *buf, u_char *ecc1, u_char *ecc2)
{
	int i, j, res;
	unsigned short status;
	uint16_t par[6], syn[6];
	uint8_t ecc[8];
	volatile unsigned short *rs_ecc;

	status = *((volatile unsigned short *)(rtc_from4_fio_base + RTC_FROM4_RS_ECC_CHK));

	if (!(status & RTC_FROM4_RS_ECC_CHK_ERROR)) {
		return 0;
	}

	/* Read the syndrom pattern from the FPGA and correct the bitorder */
	rs_ecc = (volatile unsigned short *)(rtc_from4_fio_base + RTC_FROM4_RS_ECC);
	for (i = 0; i < 8; i++) {
		ecc[i] = bitrev8(*rs_ecc);
		rs_ecc++;
	}

	/* convert into 6 10bit syndrome fields */
	par[5] = rs_decoder->index_of[(((uint16_t) ecc[0] >> 0) & 0x0ff) | (((uint16_t) ecc[1] << 8) & 0x300)];
	par[4] = rs_decoder->index_of[(((uint16_t) ecc[1] >> 2) & 0x03f) | (((uint16_t) ecc[2] << 6) & 0x3c0)];
	par[3] = rs_decoder->index_of[(((uint16_t) ecc[2] >> 4) & 0x00f) | (((uint16_t) ecc[3] << 4) & 0x3f0)];
	par[2] = rs_decoder->index_of[(((uint16_t) ecc[3] >> 6) & 0x003) | (((uint16_t) ecc[4] << 2) & 0x3fc)];
	par[1] = rs_decoder->index_of[(((uint16_t) ecc[5] >> 0) & 0x0ff) | (((uint16_t) ecc[6] << 8) & 0x300)];
	par[0] = (((uint16_t) ecc[6] >> 2) & 0x03f) | (((uint16_t) ecc[7] << 6) & 0x3c0);

	/* Convert to computable syndrome */
	for (i = 0; i < 6; i++) {
		syn[i] = par[0];
		for (j = 1; j < 6; j++)
			if (par[j] != rs_decoder->nn)
				syn[i] ^= rs_decoder->alpha_to[rs_modnn(rs_decoder, par[j] + i * j)];

		/* Convert to index form */
		syn[i] = rs_decoder->index_of[syn[i]];
	}

	/* Let the library code do its magic. */
	res = decode_rs8(rs_decoder, (uint8_t *) buf, par, 512, syn, 0, NULL, 0xff, NULL);
	if (res > 0) {
		DEBUG(MTD_DEBUG_LEVEL0, "rtc_from4_correct_data: " "ECC corrected %d errors on read\n", res);
	}
	return res;
}