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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int const int16_t ;
struct TYPE_4__ {int dmsk; int dctr; int* dptr; int* inbuf; int (* infunc ) (TYPE_1__*,int*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ JDEC ;

/* Variables and functions */
 scalar_t__ JDR_FMT1 ; 
 scalar_t__ JDR_INP ; 
 int /*<<< orphan*/  JD_SZBUF ; 
 int stub1 (TYPE_1__*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int16_t huffext (	/* >=0: decoded data, <0: error code */
	JDEC* jd,				/* Pointer to the decompressor object */
	const uint8_t* hbits,	/* Pointer to the bit distribution table */
	const uint16_t* hcode,	/* Pointer to the code word table */
	const uint8_t* hdata	/* Pointer to the data table */
)
{
	uint8_t msk, s, *dp;
	uint16_t dc, v, f, bl, nd;


	msk = jd->dmsk; dc = jd->dctr; dp = jd->dptr;	/* Bit mask, number of data available, read ptr */
	s = *dp; v = f = 0;
	bl = 16;	/* Max code length */
	do {
		if (!msk) {		/* Next byte? */
			if (!dc) {	/* No input data is available, re-fill input buffer */
				dp = jd->inbuf;	/* Top of input buffer */
				dc = jd->infunc(jd, dp, JD_SZBUF);
				if (!dc) return 0 - (int16_t)JDR_INP;	/* Err: read error or wrong stream termination */
			} else {
				dp++;	/* Next data ptr */
			}
			dc--;		/* Decrement number of available bytes */
			if (f) {		/* In flag sequence? */
				f = 0;		/* Exit flag sequence */
				if (*dp != 0) return 0 - (int16_t)JDR_FMT1;	/* Err: unexpected flag is detected (may be collapted data) */
				*dp = s = 0xFF;			/* The flag is a data 0xFF */
			} else {
				s = *dp;				/* Get next data byte */
				if (s == 0xFF) {		/* Is start of flag sequence? */
					f = 1; continue;	/* Enter flag sequence, get trailing byte */
				}
			}
			msk = 0x80;		/* Read from MSB */
		}
		v <<= 1;	/* Get a bit */
		if (s & msk) v++;
		msk >>= 1;

		for (nd = *hbits++; nd; nd--) {	/* Search the code word in this bit length */
			if (v == *hcode++) {		/* Matched? */
				jd->dmsk = msk; jd->dctr = dc; jd->dptr = dp;
				return *hdata;			/* Return the decoded data */
			}
			hdata++;
		}
		bl--;
	} while (bl);

	return 0 - (int16_t)JDR_FMT1;	/* Err: code not found (may be collapted data) */
}