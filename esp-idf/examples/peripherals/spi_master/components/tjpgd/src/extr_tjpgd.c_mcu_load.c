#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_5__ {int msx; int msy; int*** huffcode; int* dcv; int** qttbl; size_t* qtid; int scale; scalar_t__*** huffdata; scalar_t__*** huffbits; scalar_t__* mcubuf; scalar_t__ workbuf; } ;
typedef  scalar_t__ JRESULT ;
typedef  TYPE_1__ JDEC ;

/* Variables and functions */
 scalar_t__ JDR_FMT1 ; 
 scalar_t__ JDR_OK ; 
 scalar_t__ JD_USE_SCALE ; 
 int ZIG (int) ; 
 int bitext (TYPE_1__*,int) ; 
 int /*<<< orphan*/  block_idct (int*,scalar_t__*) ; 
 int huffext (TYPE_1__*,scalar_t__ const*,int const*,scalar_t__ const*) ; 

__attribute__((used)) static JRESULT mcu_load (
	JDEC* jd		/* Pointer to the decompressor object */
)
{
	int32_t *tmp = (int32_t*)jd->workbuf;	/* Block working buffer for de-quantize and IDCT */
	int b, d, e;
	uint16_t blk, nby, nbc, i, z, id, cmp;
	uint8_t *bp;
	const uint8_t *hb, *hd;
	const uint16_t *hc;
	const int32_t *dqf;


	nby = jd->msx * jd->msy;	/* Number of Y blocks (1, 2 or 4) */
	nbc = 2;					/* Number of C blocks (2) */
	bp = jd->mcubuf;			/* Pointer to the first block */

	for (blk = 0; blk < nby + nbc; blk++) {
		cmp = (blk < nby) ? 0 : blk - nby + 1;	/* Component number 0:Y, 1:Cb, 2:Cr */
		id = cmp ? 1 : 0;						/* Huffman table ID of the component */

		/* Extract a DC element from input stream */
		hb = jd->huffbits[id][0];				/* Huffman table for the DC element */
		hc = jd->huffcode[id][0];
		hd = jd->huffdata[id][0];
		b = huffext(jd, hb, hc, hd);			/* Extract a huffman coded data (bit length) */
		if (b < 0) return 0 - b;				/* Err: invalid code or input */
		d = jd->dcv[cmp];						/* DC value of previous block */
		if (b) {								/* If there is any difference from previous block */
			e = bitext(jd, b);					/* Extract data bits */
			if (e < 0) return 0 - e;			/* Err: input */
			b = 1 << (b - 1);					/* MSB position */
			if (!(e & b)) e -= (b << 1) - 1;	/* Restore sign if needed */
			d += e;								/* Get current value */
			jd->dcv[cmp] = (int16_t)d;			/* Save current DC value for next block */
		}
		dqf = jd->qttbl[jd->qtid[cmp]];			/* De-quantizer table ID for this component */
		tmp[0] = d * dqf[0] >> 8;				/* De-quantize, apply scale factor of Arai algorithm and descale 8 bits */

		/* Extract following 63 AC elements from input stream */
		for (i = 1; i < 64; tmp[i++] = 0) ;		/* Clear rest of elements */
		hb = jd->huffbits[id][1];				/* Huffman table for the AC elements */
		hc = jd->huffcode[id][1];
		hd = jd->huffdata[id][1];
		i = 1;					/* Top of the AC elements */
		do {
			b = huffext(jd, hb, hc, hd);		/* Extract a huffman coded value (zero runs and bit length) */
			if (b == 0) break;					/* EOB? */
			if (b < 0) return 0 - b;			/* Err: invalid code or input error */
			z = (uint16_t)b >> 4;				/* Number of leading zero elements */
			if (z) {
				i += z;							/* Skip zero elements */
				if (i >= 64) return JDR_FMT1;	/* Too long zero run */
			}
			if (b &= 0x0F) {					/* Bit length */
				d = bitext(jd, b);				/* Extract data bits */
				if (d < 0) return 0 - d;		/* Err: input device */
				b = 1 << (b - 1);				/* MSB position */
				if (!(d & b)) d -= (b << 1) - 1;/* Restore negative value if needed */
				z = ZIG(i);						/* Zigzag-order to raster-order converted index */
				tmp[z] = d * dqf[z] >> 8;		/* De-quantize, apply scale factor of Arai algorithm and descale 8 bits */
			}
		} while (++i < 64);		/* Next AC element */

		if (JD_USE_SCALE && jd->scale == 3) {
			*bp = (uint8_t)((*tmp / 256) + 128);	/* If scale ratio is 1/8, IDCT can be ommited and only DC element is used */
		} else {
			block_idct(tmp, bp);		/* Apply IDCT and store the block to the MCU buffer */
		}

		bp += 64;				/* Next block */
	}

	return JDR_OK;	/* All blocks have been loaded successfully */
}