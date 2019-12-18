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
typedef  int uint8_t ;
typedef  size_t uint16_t ;
struct rs_control {size_t* index_of; size_t* alpha_to; } ;

/* Variables and functions */
 int EBADMSG ; 
 int FCR ; 
 int NB_DATA ; 
 int NN ; 
 int NROOTS ; 
 int SECTOR_SIZE ; 
 int decode_rs16 (struct rs_control*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,size_t*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,size_t*) ; 
 size_t rs_modnn (struct rs_control*,int) ; 

__attribute__((used)) static int doc_ecc_decode(struct rs_control *rs, uint8_t *data, uint8_t *ecc)
{
	int i, j, nerr, errpos[8];
	uint8_t parity;
	uint16_t ds[4], s[5], tmp, errval[8], syn[4];

	/* Convert the ecc bytes into words */
	ds[0] = ((ecc[4] & 0xff) >> 0) | ((ecc[5] & 0x03) << 8);
	ds[1] = ((ecc[5] & 0xfc) >> 2) | ((ecc[2] & 0x0f) << 6);
	ds[2] = ((ecc[2] & 0xf0) >> 4) | ((ecc[3] & 0x3f) << 4);
	ds[3] = ((ecc[3] & 0xc0) >> 6) | ((ecc[0] & 0xff) << 2);
	parity = ecc[1];

	/* Initialize the syndrom buffer */
	for (i = 0; i < NROOTS; i++)
		s[i] = ds[0];
	/*
	 *  Evaluate
	 *  s[i] = ds[3]x^3 + ds[2]x^2 + ds[1]x^1 + ds[0]
	 *  where x = alpha^(FCR + i)
	 */
	for (j = 1; j < NROOTS; j++) {
		if (ds[j] == 0)
			continue;
		tmp = rs->index_of[ds[j]];
		for (i = 0; i < NROOTS; i++)
			s[i] ^= rs->alpha_to[rs_modnn(rs, tmp + (FCR + i) * j)];
	}

	/* Calc s[i] = s[i] / alpha^(v + i) */
	for (i = 0; i < NROOTS; i++) {
		if (syn[i])
			syn[i] = rs_modnn(rs, rs->index_of[s[i]] + (NN - FCR - i));
	}
	/* Call the decoder library */
	nerr = decode_rs16(rs, NULL, NULL, 1019, syn, 0, errpos, 0, errval);

	/* Incorrectable errors ? */
	if (nerr < 0)
		return nerr;

	/*
	 * Correct the errors. The bitpositions are a bit of magic,
	 * but they are given by the design of the de/encoder circuit
	 * in the DoC ASIC's.
	 */
	for (i = 0; i < nerr; i++) {
		int index, bitpos, pos = 1015 - errpos[i];
		uint8_t val;
		if (pos >= NB_DATA && pos < 1019)
			continue;
		if (pos < NB_DATA) {
			/* extract bit position (MSB first) */
			pos = 10 * (NB_DATA - 1 - pos) - 6;
			/* now correct the following 10 bits. At most two bytes
			   can be modified since pos is even */
			index = (pos >> 3) ^ 1;
			bitpos = pos & 7;
			if ((index >= 0 && index < SECTOR_SIZE) || index == (SECTOR_SIZE + 1)) {
				val = (uint8_t) (errval[i] >> (2 + bitpos));
				parity ^= val;
				if (index < SECTOR_SIZE)
					data[index] ^= val;
			}
			index = ((pos >> 3) + 1) ^ 1;
			bitpos = (bitpos + 10) & 7;
			if (bitpos == 0)
				bitpos = 8;
			if ((index >= 0 && index < SECTOR_SIZE) || index == (SECTOR_SIZE + 1)) {
				val = (uint8_t) (errval[i] << (8 - bitpos));
				parity ^= val;
				if (index < SECTOR_SIZE)
					data[index] ^= val;
			}
		}
	}
	/* If the parity is wrong, no rescue possible */
	return parity ? -EBADMSG : nerr;
}